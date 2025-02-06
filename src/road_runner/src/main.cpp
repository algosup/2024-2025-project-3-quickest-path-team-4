#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <limits>
#include <unordered_map>
#include <optional>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>
#include "graph_data.h"
#include "graph_loader.h"
#include "Bidirectional_Astar.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;
using namespace std;
using namespace boost::property_tree;

GraphData g_data;

string create_error_json(const string& message) {
    ptree pt;
    pt.put("error", message);
    stringstream ss;
    write_json(ss, pt);
    return ss.str();
}

string generate_json(const vector<int>& path, long long execution_time) {
    ptree pt;
    ptree path_array;
    for (const auto& node : path) {
        ptree node_obj;
        node_obj.put("", node);
        path_array.push_back(make_pair("", node_obj));
    }
    pt.add_child("path", path_array);
    pt.put("execution_time_ms", execution_time);
    stringstream ss;
    write_json(ss, pt);
    return ss.str();
}

bool init_graph_data() {
    try {
        const string graph_file = "../data/USA-roads.csv";
        auto result = GraphLoader::load_from_csv(graph_file);
        if (!result) {
            cerr << "Failed to load graph data" << endl;
            return false;
        }
        g_data = *result;
        std::cout << "Graph loaded successfully: "
                 << g_data.size() << " nodes, "
                 << g_data.get_edge_count() << " edges" << std::endl;
        return true;
    } catch (const exception& e) {
        cerr << "Failed to load graph data: " << e.what() << endl;
        return false;
    }
}

template<class Body, class Allocator>
http::response<http::string_body> 
handle_request(http::request<Body, http::basic_fields<Allocator>>&& req) {
    auto const send_response = 
        [&req](http::status status, const string& body, const string& content_type) {
            http::response<http::string_body> res{status, req.version()};
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, content_type);
            res.set(http::field::access_control_allow_origin, "*");
            res.keep_alive(req.keep_alive());
            res.body() = body;
            res.prepare_payload();
            return res;
        };

    try {
        string target = string(req.target());
        if (target.find("/path?") != 0) {
            return send_response(
                http::status::bad_request,
                create_error_json("Invalid endpoint. Use /path?start=<start>&end=<end>"),
                "application/json"
            );
        }

        size_t start_pos = target.find("start=");
        size_t end_pos = target.find("end=");
        
        if (start_pos == string::npos || end_pos == string::npos) {
            return send_response(
                http::status::bad_request,
                create_error_json("Missing parameters. Provide 'start' and 'end'."),
                "application/json"
            );
        }

        start_pos += 6;
        end_pos += 4;
        
        size_t start_end = target.find("&", start_pos);
        size_t end_end = target.find("&", end_pos);
        
        int start = stoi(target.substr(start_pos, start_end - start_pos));
        int end = stoi(target.substr(end_pos, end_end - end_pos));

        if (start < 0 || start >= g_data.size() || 
        end < 0 || end >= g_data.size()) {
        return send_response(
            http::status::bad_request,
            create_error_json("Invalid node IDs"),
            "application/json"
        );
}

        vector<int> distances(g_data.size(), numeric_limits<int>::max());
        distances[start] = 0;

        auto begin = chrono::steady_clock::now();
        auto path_opt = bidirectional_astar(g_data, start, end, distances);
        auto end_time = chrono::steady_clock::now();
        auto execution_time = chrono::duration_cast<chrono::milliseconds>(end_time - begin).count();

        if (!path_opt) {
            return send_response(
                http::status::ok,
                create_error_json("No path found between the specified nodes."),
                "application/json"
            );
        }

        return send_response(
            http::status::ok,
            generate_json(*path_opt, execution_time),
            "application/json"
        );

    } catch (const exception& e) {
        return send_response(
            http::status::internal_server_error,
            create_error_json("Server error: " + string(e.what())),
            "application/json"
        );
    }
}

int main() {
    cout << "Loading graph data...\n";

    if (!init_graph_data()) {
        cerr << "Failed to initialize graph data. Exiting." << endl;
        return 1;
    }

    try {
        auto const address = net::ip::make_address("127.0.0.1");
        auto const port = static_cast<unsigned short>(8080);
        net::io_context ioc{1};
        tcp::acceptor acceptor{ioc, {address, port}};
        
        cout << "Server running at http://127.0.0.1:8080" << endl;

        while (true) {
            tcp::socket socket{ioc};
            acceptor.accept(socket);
            beast::flat_buffer buffer;
            http::request<http::string_body> req;
            http::read(socket, buffer, req);
            auto res = handle_request(std::move(req));
            http::write(socket, res);
            socket.shutdown(tcp::socket::shutdown_send);
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}