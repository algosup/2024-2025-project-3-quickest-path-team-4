#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <optional>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <filesystem>
#include "graphData.h"
#include "algorithm.h"
#include "loading.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using namespace std;
using tcp = net::ip::tcp;

const string SEPARATOR = "════════════════════════════════════════════════════════════";
const string SUBSEPARATOR = "────────────────────────────────────────────────────────";

#if defined(__APPLE__) && defined(__MACH__)
string get_timestamp()
{
    auto now = chrono::system_clock::now();
    auto now_time = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&now_time), "[%Y-%m-%d %H:%M:%S]");
    return ss.str();
}
#endif

void log_message(const string &category, const string &message, bool important = false)
{
    // Skip detailed path logging
    if (category == "PATH" || category == "PARAM")
    {
        return;
    }

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
const graph_data g_data = load_graph_data(file_path);

string to_json(int start, int end, const vector<int> &path, long duration, int total_dist)
{
    stringstream ss;
    ss << "{\n"
       << "    \"start\": " << start << ",\n"
       << "    \"end\": " << end << ",\n"
       << "    \"nodes_explored\": " << path.size() << ",\n"
       << "    \"path\": [";

    for (size_t i = 0; i < path.size(); ++i)
    {
        ss << path[i];
        if (i < path.size() - 1)
        {
            ss << ", ";
        }
    }

    ss << "],\n"
       << "    \"distance\": " << total_dist << ",\n"
       << "    \"computation_time\": " << duration << "\n"
       << "}\n";

    return ss.str();
}

string to_xml(int start, int end, const vector<int> &path, long duration, int total_dist)
{
    stringstream ss;
    ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
       << "<response>\n"
       << "    <start>" << start << "</start>\n"
       << "    <end>" << end << "</end>\n"
       << "    <nodes_explored>" << path.size() << "</nodes_explored>\n"
       << "    <path>\n"
       << "        ";

    for (size_t i = 0; i < path.size(); ++i)
    {
        if (i % 10 == 0 && i > 0)
        {
            ss << "\n        ";
        }
        if (i == path.size() - 1)
        {
            ss << "<node style=\"color: red\">" << path[i] << "</node>";
        }
        else
        {
            ss << "<node>" << path[i] << "</node>";
            if (i < path.size() - 1)
            {
                ss << " → ";
            }
        }
    }

    ss << "\n    </path>\n"
       << "    <distance>" << total_dist << "</distance>\n"
       << "    <computation_time>" << duration << "</computation_time>\n"
       << "</response>\n";

    return ss.str();
}

void save_to_file(const string &filename, const string &content)
{
    ofstream file(filename);
    if (file.is_open())
    {
        file << content;
        file.close();
        log_message("FILE", "Successfully saved to " + filename);
    }
    else
    {
        log_message("ERROR", "Failed to save file: " + filename);
    }
}

void ensure_output_directory(const string &path)
{
    filesystem::path dir_path = filesystem::absolute(filesystem::path(path));
    if (!filesystem::exists(dir_path))
    {
        try
        {
            filesystem::create_directories(dir_path);
            log_message("DIRECTORY", "Created output directory: " + dir_path.string());
        }
        catch (const filesystem::filesystem_error &e)
        {
            log_message("ERROR", "Failed to create directory: " + string(e.what()));
        }
    }
}
void handle_request(const http::request<http::string_body> &req, http::response<http::string_body> &res)
{

    cout << SUBSEPARATOR << endl;
    log_message("REQUEST", "New path request received", true);

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
        vector<int> distances(g_data.adjacency.size(), numeric_limits<int>::max());

        if (query.find('?') != string::npos)
        {
            size_t pos = query.find('?') + 1;
            string params = query.substr(pos);
            stringstream param_stream(params);
            string param;

            while (getline(param_stream, param, '&'))
            {
                size_t eq_pos = param.find('=');
                if (eq_pos != string::npos)
                {
                    string key = param.substr(0, eq_pos);
                    string value = param.substr(eq_pos + 1);

                    try
                    {
                        if (key == "start")
                        {
                            start = stoi(value);
                            log_message("PARAM", "Start node: " + value);
                        }
                        else if (key == "end")
                        {
                            end = stoi(value);
                            log_message("PARAM", "End node: " + value);
                        }
                    }
                    catch (const exception &e)
                    {
                        log_message("ERROR", "Invalid parameter value: " + value);
                    }
                }
            }
        }

        if (start == -1 || end == -1)
        {
            res.result(http::status::bad_request);
            res.body() = "Missing start or end node.";
            res.set(http::field::content_type, "text/plain");
            res.prepare_payload();
            return;
        }

        // Compute path
        log_message("PROCESS", "Starting path computation...");
        auto begin = chrono::steady_clock::now();
        auto result = bidirectional_astar(g_data, start, end, distances);
        auto end_time = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - begin).count();
        log_message("COMPLETE", "Path computation finished in " + to_string(duration) + "ms", true);

        if (result.has_value())
        {
            string filename, content;
            int path_distance = distances[end];

            // Calculate actual path distance by summing edge weights
            path_distance = 0;
            const vector<int> &path = result.value();
            for (size_t i = 0; i < path.size() - 1; ++i)
            {
                int curr = path[i];
                int next = path[i + 1];
                for (const auto &[adj_node, weight] : g_data.adjacency[curr])
                {
                    if (adj_node == next)
                    {
                        path_distance += weight;
                        break;
                    }
                }
            }

            if (path_distance == 0 && start != end)
            {
                log_message("ERROR", "Failed to compute path distance");
                res.result(http::status::internal_server_error);
                res.body() = "Error computing path distance";
                res.prepare_payload();
                return;
            }
            log_message("INFO", "Found path from " + to_string(start) +
                                    " to " + to_string(end) +
                                    " (distance: " + to_string(path_distance) + ")");

            ensure_output_directory("output");

            if (response_type == "xml")
            {
                filename = "output/path_result.xml";
                content = to_xml(start, end, result.value(), duration, path_distance);
                res.set(http::field::content_type, "application/xml");
            }
            else
            {
                filename = "output/path_result.json";
                content = to_json(start, end, result.value(), duration, path_distance);
                res.set(http::field::content_type, "application/json");
            }

            save_to_file(filename, content);
            res.result(http::status::ok);
            res.set(http::field::content_disposition, "attachment; filename=" +
                                                          filesystem::path(filename).filename().string());
            res.body() = content;
            log_message("INFO", "Path found - Distance: " + to_string(path_distance) +
                                    "m, Time: " + to_string(duration) + "ms");

            ensure_output_directory("output");

            if (response_type == "xml")
            {
                filename = "output/path_result.xml";
                content = to_xml(start, end, result.value(), duration, path_distance);
                res.set(http::field::content_type, "application/xml");
            }
            else
            {
                filename = "output/path_result.json";
                content = to_json(start, end, result.value(), duration, path_distance);
                res.set(http::field::content_type, "application/json");
            }

            save_to_file(filename, content);
            res.result(http::status::ok);
            res.set(http::field::content_disposition, "attachment; filename=" +
                                                          filesystem::path(filename).filename().string());
            res.body() = content;
            log_message("SUCCESS", "File saved: " + filename);
        }
        else
        {
            log_message("INFO", "No path found");
            res.result(http::status::not_found);
            res.body() = "No path found";
            res.set(http::field::content_type, "text/plain");
        }

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
                http::read(socket, buffer, req, ec);

                if (ec == http::error::end_of_stream)
                    break;
                if (ec)
                    throw beast::system_error{ec};

                keep_alive = req.keep_alive();
                http::response<http::string_body> res;
                handle_request(req, res);
                res.keep_alive(keep_alive);
                http::write(socket, res, ec);

                if (ec || !keep_alive)
                    break;
            }

            socket.shutdown(tcp::socket::shutdown_both, ec);
            socket.close();
        }
        catch (const std::exception &e)
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

            while (true)
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