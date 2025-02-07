// clang++ -std=gnu++20 -O3 -I../boost_1_82_0 server.cpp Bidirectional_Astar.cpp loading.cpp -o server -lpthread

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <optional>
#include <cstdlib> // For system()
#include <thread>
#include <chrono>
#include "graphData.h"
#include "algorithm.h"
#include "loading.h"
#include "saveLoadBinaryCompressed.h" // Include the header for loading compressed paths

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using namespace std;
using tcp = net::ip::tcp;

const string SEPARATOR = "════════════════════════════════════════════════════════════";
const string SUBSEPARATOR = "────────────────────────────────────────────────────────";


//Check if the computer is mac or windows and use the correct function
#if defined(__APPLE__) && defined(__MACH__)
string get_timestamp()
{
    auto now = chrono::system_clock::now();
    auto now_time = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&now_time), "[%Y-%m-%d %H:%M:%S]");
    return ss.str();
}
#elif defined(_WIN32) || defined(_WIN64)
string get_timestamp()
{
    auto now = chrono::system_clock::now();
    auto now_time = chrono::system_clock::to_time_t(now);
    struct tm tm;
    localtime_s(&tm, &now_time);  // Use localtime_s instead of localtime
    stringstream ss;
    ss << put_time(&tm, "[%Y-%m-%d %H:%M:%S]");
    return ss.str();
}
#endif

// Helper function for consistent log formatting
void log_message(const string &category, const string &message, bool important = false)
{
    cout << get_timestamp() << " ";
    if (important)
    {
        cout << "║ \033[1;32m" << left << setw(12) << category << "\033[0m │ " << message << endl;
    }
    else
    {
        cout << "║ " << left << setw(12) << category << " │ " << message << endl;
    }
}

string file_path = "USA-roads.csv";
string compressed_paths_file = "compressed_paths.bin";

const graph_data g_data = load_graph_data(file_path);
unordered_map<int, int> single_neighbors;

// Convert response to JSON format
string to_json(int start, int end, const vector<int> &path, long duration, int total_dist)
{
    stringstream ss;
    ss << "{\n"
       << "    \"start\": " << start << ",\n"
       << "    \"end\": " << end << ",\n"
       << "    \"nodes_explored\": " << path.size() << ",\n"
       << "    \"distance\": " << total_dist << ",\n"
       << "    \"computation_time\": " << duration << "\n"
       << "}" "\n";

    return ss.str();
}

// Convert response to XML format
string to_xml(int start, int end, const vector<int> &path, long duration, int distance)
{
    stringstream ss;
    ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
       << "<response>\n"
       << "    <start>" << start << "</start>\n"
       << "    <end>" << end << "</end>\n"
       << "    <path>\n";

    // Format path nodes with proper indentation
    for (int node : path)
    {
        ss << "        <node>" << node << "</node>\n";
    }

    ss << "    </path>\n"
       << "    <distance>" << distance << "</distance>\n"
       << "    <computation_time>" << duration << "</computation_time>\n"
       << "</response>";

    return ss.str();
}

void handle_request(const http::request<http::string_body>& req, http::response<http::string_body>& res)
{
    cout << SUBSEPARATOR << endl;
    log_message("REQUEST", "New request received", true);
    log_message("PATH", string(req.target()));

    string response_type = "json"; // Default to JSON
    if (req.find(http::field::accept) != req.end())
    {
        string accept_header = req[http::field::accept];
        if (accept_header.find("application/xml") != string::npos)
        {
            response_type = "xml";
        }
    }
    log_message("FORMAT", "Response type: " + response_type);

    if (req.method() == http::verb::get && req.target().starts_with("/path"))
    {
        string query(req.target().begin(), req.target().end());
        log_message("DEBUG", "Processing query: " + query);
        
        int start = -1, end = -1;
        vector<int> distances(g_data.adjacency.size(), numeric_limits<int>::max());
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
                    log_message("DEBUG", "Parsed parameter: " + key + "=" + value);
                }
            }

            try {
                if (params.find("start") != params.end() && params.find("end") != params.end()) {
                    start = stoi(params["start"]);
                    end = stoi(params["end"]);
                    
                    // Validate nodes and graph
                    if (start < 0 || end < 0 || start >= g_data.adjacency.size() || end >= g_data.adjacency.size()) {
                        log_message("ERROR", "Node out of range. Graph size: " + to_string(g_data.adjacency.size()));
                        throw std::out_of_range("Node index out of range");
                    }
                    
                    // Debug connectivity and path possibilities
                    log_message("DEBUG", "Start node " + to_string(start) + " neighbors:");
                    for (const auto& neighbor : g_data.adjacency[start]) {
                        log_message("DEBUG", "  -> Node " + to_string(neighbor.first) + " (weight: " + to_string(neighbor.second) + ")");
                    }
                    
                    log_message("DEBUG", "End node " + to_string(end) + " neighbors:");
                    for (const auto& neighbor : g_data.adjacency[end]) {
                        log_message("DEBUG", "  -> Node " + to_string(neighbor.first) + " (weight: " + to_string(neighbor.second) + ")");
                    }
                    
                    log_message("DEBUG", "Graph size: " + to_string(g_data.adjacency.size()));
                    log_message("DEBUG", "Attempting path computation...");
                } else {
                    log_message("ERROR", "Missing start or end parameters");
                    throw std::invalid_argument("Missing parameters");
                }
            }
            catch (const std::exception& e) {
                res.result(http::status::bad_request);
                res.body() = "Invalid parameters: " + string(e.what());
                res.set(http::field::content_type, "text/plain");
                res.prepare_payload();
                return;
            }
        }

        // Stylized log for Start and End nodes
        stringstream nodes_message;
        nodes_message << "Start: " << start << " End: " << end;
        log_message("NODES", nodes_message.str());

        if (start == -1 || end == -1)
        {
            res.result(http::status::bad_request);
            res.body() = "Missing start or end node.";
            res.set(http::field::content_type, "text/plain");
            res.prepare_payload();
            return;
        }

        int true_start = start, true_end = end;
        distances[start] = 0;

        log_message("PROCESS", "Starting path computation...");
        auto begin = chrono::steady_clock::now();
        auto result = bidirectional_astar(g_data, start, end, distances);
        auto end_time = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - begin).count();
        log_message("COMPLETE", "Path computation finished in " + to_string(duration) + "ms", true);

        res.result(http::status::ok);
        if (result.has_value())
        {
            string filename;
            string content;
            int path_distance = distances[end];

            if (path_distance == numeric_limits<int>::max()) {
                log_message("ERROR", "Invalid path distance computed");
                res.result(http::status::internal_server_error);
                res.body() = "Error computing path distance";
                res.prepare_payload();
                return;
            }

            log_message("DISTANCE", "Total distance: " + to_string(path_distance));

            if (response_type == "xml")
            {
                filename = "path_result.xml";
                content = to_xml(true_start, true_end, result.value(), duration, path_distance);
                res.set(http::field::content_type, "application/xml");
            }
            else
            {
                filename = "path_result.json";
                content = to_json(true_start, true_end, result.value(), duration, path_distance);
                res.set(http::field::content_type, "application/json");
            }

            res.result(http::status::ok);
            res.set(http::field::content_disposition, "attachment; filename=" + filename);
            res.body() = content;
        }
        else
        {
            res.result(http::status::not_found);
            res.body() = "No path found from " + to_string(true_start) + " to " + to_string(true_end);
            res.set(http::field::content_type, "text/plain");
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
        bool keep_alive = true;
        boost::system::error_code ec;
        
        while (keep_alive && socket.is_open())
        {
            beast::flat_buffer buffer;
            http::request<http::string_body> req;
            
            log_message("DEBUG", "Waiting for request...");
            http::read(socket, buffer, req, ec);
            
            if (ec == http::error::end_of_stream)
            {
                log_message("DEBUG", "Client closed connection");
                break;
            }
            
            if (ec)
            {
                log_message("ERROR", "Read error: " + ec.message());
                throw beast::system_error{ec};
            }
            
            log_message("SESSION", "New session started");
            log_message("DEBUG", "Request path: " + string(req.target()));
            
            keep_alive = req.keep_alive();
            
            http::response<http::string_body> res;
            handle_request(req, res);   // Removed compressed_paths parameter
            res.keep_alive(keep_alive);
            
            log_message("DEBUG", "Sending response...");
            http::write(socket, res, ec);
            
            if (ec)
            {
                log_message("ERROR", "Write error: " + ec.message());
                throw beast::system_error{ec};
            }
            
            if (!keep_alive)
            {
                log_message("DEBUG", "Connection not keep-alive, closing");
                break;
            }
        }
        
        socket.shutdown(tcp::socket::shutdown_both, ec);
        socket.close();
    }
    catch (const std::exception& e)
    {
        log_message("ERROR", "Session error: " + string(e.what()));
        socket.close();
    }
}

int main()
{   
    cout << SEPARATOR << endl;
    log_message("STARTUP", "Initializing server...", true);
    
    try 
    {
        net::io_context ioc;
        tcp::acceptor acceptor{ioc, tcp::endpoint(tcp::v4(), 8080)};
        acceptor.set_option(net::socket_base::reuse_address(true));
        log_message("SERVER", "Listening on port 8080", true);
        cout << SEPARATOR << endl;

        while (true)  // Add main server loop
        {
            tcp::socket socket{ioc};
            acceptor.accept(socket);
            std::thread(&do_session, std::move(socket)).detach();
        }
    }
    catch (exception &e)
    {
        log_message("ERROR", string("Fatal error: ") + e.what());
        return 1;
    }

    return 0;
}