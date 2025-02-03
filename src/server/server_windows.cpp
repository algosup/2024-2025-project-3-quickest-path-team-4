#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <optional>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <iomanip>
#ifdef _WIN32
#include <windows.h>
#endif
#include "graph_data.h"
#include "Dijkstra.cpp"
#include "loading.cpp"
#include "preprocess.cpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using namespace std;
using tcp = net::ip::tcp;

const string SEPARATOR = "════════════════════════════════════════════════════════════";
const string SUBSEPARATOR = "────────────────────────────────────────────────────────";

#ifdef _WIN32
void initialize_windows_console()
{
    // Enable ANSI escape sequences for Windows console
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

string get_timestamp()
{
    auto now = chrono::system_clock::now();
    auto now_time = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&now_time), "[%Y-%m-%d %H:%M:%S]");
    return ss.str();
}

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

// Load graph data with platform-independent path handling
graph_data gdata = load_graph_data("USA-roads.csv");
unordered_map<int, int> single_neighbors;

string to_json(int start, int end, const vector<int> &path, long duration)
{
    stringstream ss;
    ss << "{\n"
       << "    \"start\": " << start << ",\n"
       << "    \"end\": " << end << ",\n"
       << "    \"path\": [";

    for (size_t i = 0; i < path.size(); ++i)
    {
        if (i % 10 == 0 && i != 0)
        {
            ss << "\n        ";
        }
        ss << path[i];
        if (i < path.size() - 1)
            ss << ", ";
    }

    ss << "],\n"
       << "    \"computation_time\": " << duration << "\n"
       << "}";

    return ss.str();
}

string to_xml(int start, int end, const vector<int> &path, long duration)
{
    stringstream ss;
    ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
       << "<response>\n"
       << "    <start>" << start << "</start>\n"
       << "    <end>" << end << "</end>\n"
       << "    <path>\n";

    for (int node : path)
    {
        ss << "        <node>" << node << "</node>\n";
    }

    ss << "    </path>\n"
       << "    <computation_time>" << duration << "</computation_time>\n"
       << "</response>";

    return ss.str();
}

void handle_request(const http::request<http::string_body> &req, http::response<http::string_body> &res)
{
    cout << SUBSEPARATOR << endl;
    log_message("REQUEST", "New request received", true);
    log_message("PATH", string(req.target()));

    string response_type = "json";
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

        are_extremities_singles are_they;
        unordered_map<int, int> distances;
        for (const auto &[node, _] : gdata.adjacency)
        {
            distances[node] = numeric_limits<int>::max();
        }
        int true_start = start, true_end = end;
        distances[start] = 0;
        check_single_start_or_end(&start, &end, &single_neighbors, &are_they);

        log_message("PROCESS", "Starting path computation...");
        auto begin = chrono::steady_clock::now();
        auto result = bidirectional_astar(gdata, start, end, distances);
        auto end_time = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - begin).count();
        log_message("COMPLETE", "Path computation finished in " + to_string(duration) + "ms", true);

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
    bool keep_alive = true;

    while (keep_alive)
    {
        try
        {
            beast::flat_buffer buffer;
            http::request<http::string_body> req;

            // Read the request
            beast::error_code ec;
            http::read(socket, buffer, req, ec);

            if (ec == http::error::end_of_stream)
            {
                break; // Client closed connection
            }

            if (ec)
            {
                throw beast::system_error{ec};
            }

            // Check if we should keep alive
            keep_alive = req.keep_alive();

            // Handle the request
            http::response<http::string_body> res;
            handle_request(req, res);

            // Set keep-alive header in response
            res.keep_alive(keep_alive);

            // Send the response
            http::write(socket, res, ec);

            if (ec)
            {
                throw beast::system_error{ec};
            }
        }
        catch (exception &e)
        {
            log_message("ERROR", string("Session error: ") + e.what());
            break;
        }
    }

    // Gracefully close the socket
    beast::error_code ec;
    socket.shutdown(tcp::socket::shutdown_send, ec);
}

int main()
{
#ifdef _WIN32
    initialize_windows_console();
#endif

    cout << SEPARATOR << endl;
    log_message("STARTUP", "Initializing server...", true);

    preprocess(&gdata, &single_neighbors);

    try
    {
        net::io_context ioc;
        tcp::acceptor acceptor{ioc, tcp::endpoint(tcp::v4(), 8080)};
        acceptor.set_option(net::socket_base::reuse_address(true));
        log_message("SERVER", "Listening on port 8080", true);
        cout << SEPARATOR << endl;

        while (true)
        {
            tcp::socket socket(ioc);
            acceptor.accept(socket);
            do_session(std::move(socket));
        }
    }
    catch (exception &e)
    {
        log_message("ERROR", string("Fatal error: ") + e.what());
    }
    return 0;
}