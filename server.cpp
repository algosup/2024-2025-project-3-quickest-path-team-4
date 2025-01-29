#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <optional>
#include <cstdlib> // For system()
#include <thread>
#include <chrono>
#include "graph_data.h"
#include "Dijkstra.cpp"
#include "loading.cpp"
#include "preprocess.cpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using namespace std;
using tcp = net::ip::tcp;

graph_data gdata = load_graph_data("USA-roads.csv");
unordered_map<int, int> single_neighbors;

// Function to start Ngrok and fetch the public URL
string start_ngrok()
{
    system("ngrok http 8080 --log=stdout > ngrok.log 2>&1 &");
    this_thread::sleep_for(chrono::seconds(3)); // Give Ngrok time to start

    FILE *pipe = popen("curl -s http://localhost:4040/api/tunnels | jq -r '.tunnels[0].public_url'", "r");
    if (!pipe)
        return "";
    char buffer[128];
    string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

// Convert response to JSON format
string to_json(int start, int end, const vector<int> &path, long duration)
{
    stringstream ss;
    ss << "{\"start\": " << start << ", \"end\": " << end << ", \"path\": [";
    for (size_t i = 0; i < path.size(); ++i)
    {
        ss << path[i];
        if (i < path.size() - 1)
            ss << ", ";
    }
    ss << "], \"computation_time\": " << duration << "}";
    return ss.str();
}

// Convert response to XML format
string to_xml(int start, int end, const vector<int> &path, long duration)
{
    stringstream ss;
    ss << "<response><start>" << start << "</start><end>" << end << "</end><path>";
    for (int node : path)
    {
        ss << "<node>" << node << "</node>";
    }
    ss << "</path><computation_time>" << duration << "</computation_time></response>";
    return ss.str();
}

void handle_request(const http::request<http::string_body> &req, http::response<http::string_body> &res)
{
    cout << "Received request: " << req.target() << endl;
    string response_type = "json";
    if (req.find(http::field::accept) != req.end())
    {
        string accept_header = req[http::field::accept];
        if (accept_header.find("application/xml") != string::npos)
        {
            response_type = "xml";
        }
    }

    if (req.method() == http::verb::get && req.target().starts_with("/path"))
    {
        string query(req.target().begin(), req.target().end());
        int start = -1, end = -1;
        unordered_map<string, string> params;

        if (query.find('?') != string::npos)
        {
            query = query.substr(query.find('?') + 1);
            stringstream ss(query);
            string token;

            while (getline(ss, token, '&'))
            {
                auto pos = token.find('=');
                if (pos != string::npos)
                {
                    string key = token.substr(0, pos);
                    string value = token.substr(pos + 1);
                    params[key] = value;
                }
            }
            if (params.find("start") != params.end() && params.find("end") != params.end())
            {
                try
                {
                    start = stoi(params["start"]);
                    end = stoi(params["end"]);
                }
                catch (const exception &)
                {
                    res.result(http::status::bad_request);
                    res.body() = "Invalid start or end node.";
                    res.set(http::field::content_type, "text/plain");
                    res.prepare_payload();
                    return;
                }
            }
        }

        cout << "Start: " << start << " End: " << end << endl;

        if (start == -1 || end == -1)
        {
            res.result(http::status::bad_request);
            res.body() = "Missing start or end node.";
            res.set(http::field::content_type, "text/plain");
            res.prepare_payload();
            return;
        }

        are_extremities_singles are_they;
        unordered_map<int, int> distances;
        for (const auto &[node, _] : gdata.adjacency)
        {
            distances[node] = numeric_limits<int>::max();
        }
        int true_start = start, true_end = end;
        distances[start] = 0;
        check_single_start_or_end(&start, &end, &single_neighbors, &are_they);

        cout << "Starting to find the path" << endl;
        auto begin = chrono::steady_clock::now();
        auto result = bidirectional_dijkstra(gdata, start, end, &distances);
        auto end_time = chrono::steady_clock::now();
        cout << "Path computation finished" << endl;

        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - begin).count();
        cout << "Path computation took " << duration << " ms" << endl;

        res.result(http::status::ok);
        if (result.has_value())
        {
            if (response_type == "xml")
            {
                res.set(http::field::content_type, "application/xml");
                res.body() = to_xml(true_start, true_end, result.value(), duration);
            }
            else
            {
                res.set(http::field::content_type, "application/json");
                res.body() = to_json(true_start, true_end, result.value(), duration);
            }
        }
        else
        {
            res.body() = "No path found from " + to_string(true_start) + " to " + to_string(true_end);
        }
        res.prepare_payload();
    }
    else
    {
        res.result(http::status::not_found);
        res.body() = "Route not found.";
        res.set(http::field::content_type, "text/plain");
        res.prepare_payload();
    }
}

void do_session(tcp::socket socket)
{
    try
    {
        beast::flat_buffer buffer;
        http::request<http::string_body> req;
        http::read(socket, buffer, req);
        cout << "Handling new session" << endl;
        http::response<http::string_body> res;
        handle_request(req, res);
        http::write(socket, res);
    }
    catch (exception &e)
    {
        cerr << "Session error: " << e.what() << endl;
    }
}

int main()
{
    preprocess(&gdata, &single_neighbors);
    string ngrok_url = start_ngrok();
    cout << "Public Ngrok URL: " << ngrok_url << endl;

    try
    {
        net::io_context ioc;
        tcp::acceptor acceptor{ioc, tcp::endpoint(tcp::v4(), 8080)};
        acceptor.set_option(net::socket_base::reuse_address(true));
        cout << "Server is listening on 8080" << endl;

        while (true)
        {
            tcp::socket socket(ioc);
            acceptor.accept(socket);
            cout << "New connection accepted" << endl;
            do_session(std::move(socket));
        }
    }
    catch (exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
