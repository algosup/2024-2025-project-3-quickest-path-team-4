#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/signal_set.hpp>
#include <atomic>
#include <memory>
#include <csignal>
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

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using namespace std;
using tcp = net::ip::tcp;

// Constants
const string SEPARATOR = "════════════════════════════════════════════════════════════";
const string SUBSEPARATOR = "────────────────────────────────────────────────────────";

// Forward declarations
class Session;
class Listener;
void log_message(const string& category, const string& message, bool important = false);
void handle_request(const http::request<http::string_body>& req, 
                   http::response<http::string_body>& res, 
                   const GraphData& g_data);

// Utility functions
string get_timestamp() {
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void log_message(const string& category, const string& message, bool important) {
    cout << "[" << get_timestamp() << "] ║ "
         << left << setw(12) << category << "│ " << message << endl;
    if (important) cout << SUBSEPARATOR << endl;
}

void ensure_output_directory(const string& path) {
    filesystem::path dir(path);
    if (!filesystem::exists(dir)) {
        filesystem::create_directories(dir);
    }
}

void save_to_file(const string& filename, const string& content) {
    ensure_output_directory("output");
    ofstream file("output/" + filename);
    if (file.is_open()) {
        file << content;
        file.close();
    }
}

// Data formatting functions
string to_json(int start, int end, const vector<int>& path, long duration, int total_dist) {
    stringstream ss;
    ss << "{\n"
       << "    \"start\": " << start << ",\n"
       << "    \"end\": " << end << ",\n"
       << "    \"path\": [\n        ";
    
    for (size_t i = 0; i < path.size(); ++i) {
        ss << path[i];
        if (i < path.size() - 1) ss << ", ";
        if ((i + 1) % 10 == 0 && i < path.size() - 1) ss << "\n        ";
    }
    
    ss << "\n    ],\n"
       << "    \"total_nodes_explored\": " << path.size() << ",\n"
       << "    \"distance\": " << total_dist << ",\n"
       << "    \"computation_time\": \"" << duration << "ms\"\n"
       << "}\n";
    
    return ss.str();
}

string to_xml(int start, int end, const vector<int>& path, long duration, int total_dist) {
    stringstream ss;
    ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
       << "<path_result>\n"
       << "    <start>" << start << "</start>\n"
       << "    <end>" << end << "</end>\n"
       << "    <path>\n        ";
    
    for (size_t i = 0; i < path.size(); ++i) {
        ss << path[i];
        if (i < path.size() - 1) ss << ", ";
        if ((i + 1) % 10 == 0 && i < path.size() - 1) ss << "\n        ";
    }
    
    ss << "\n    </path>\n"
       << "    <nodes_explored>" << path.size() << "</nodes_explored>\n"
       << "    <distance>" << total_dist << "</distance>\n"
       << "    <computation_time>" << duration << "ms</computation_time>\n"
       << "</path_result>\n";
    
    return ss.str();
}


class Session : public std::enable_shared_from_this<Session> {
    private:
        beast::tcp_stream stream_;
        beast::flat_buffer buffer_;
        http::request<http::string_body> req_;
        std::shared_ptr<http::response<http::string_body>> res_;
        const GraphData& graph_data_;
        std::atomic<bool>& running_;
    
    public:
        Session(tcp::socket&& socket, const GraphData& g_data, std::atomic<bool>& running)
            : stream_(std::move(socket))
            , graph_data_(g_data)
            , running_(running) {
            stream_.expires_after(std::chrono::seconds(30));
        }
    
        void run() {
            do_read();
        }
    
    private:
        void do_read() {
            req_ = {};
            buffer_.clear();
    
            http::async_read(stream_, buffer_, req_,
                beast::bind_front_handler(
                    &Session::on_read,
                    shared_from_this()));
        }
    
        void on_read(beast::error_code ec, std::size_t) {
            if (ec) {
                if (ec == http::error::end_of_stream) {
                    return do_close();
                }
                log_message("ERROR", "Read failed: " + ec.message());
                return;
            }
    
            auto sp = std::make_shared<http::response<http::string_body>>();
            res_ = sp;
    
            try {
                handle_request(req_, *sp, graph_data_);
            }
            catch (const std::exception& e) {
                log_message("ERROR", string("Request handling error: ") + e.what());
                sp->result(http::status::internal_server_error);
                sp->set(http::field::content_type, "text/plain");
                sp->body() = "Internal server error";
            }
    
            sp->keep_alive(req_.keep_alive());
            sp->prepare_payload();
    
            http::async_write(stream_, *sp,
                beast::bind_front_handler(
                    &Session::on_write,
                    shared_from_this()));
        }
    
        void on_write(beast::error_code ec, std::size_t) {
            if (ec) {
                log_message("ERROR", "Write failed: " + ec.message());
                return;
            }
    
            if (!req_.keep_alive() || !running_) {
                return do_close();
            }
    
            stream_.expires_after(std::chrono::seconds(30));
            do_read();
        }
    
        void do_close() {
            beast::error_code ec;
            stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
        }
    };
    
    class Listener : public std::enable_shared_from_this<Listener> {
    private:
        tcp::acceptor acceptor_;
        net::io_context& ioc_;
        const GraphData& graph_data_;
        std::atomic<bool>& running_;
    
    public:
        Listener(net::io_context& ioc, tcp::endpoint endpoint, const GraphData& g_data, std::atomic<bool>& running)
            : acceptor_(ioc)
            , ioc_(ioc)
            , graph_data_(g_data)
            , running_(running) {
            beast::error_code ec;
    
            acceptor_.open(endpoint.protocol(), ec);
            if (ec) {
                log_message("ERROR", "Open failed: " + ec.message());
                return;
            }
    
            acceptor_.set_option(net::socket_base::reuse_address(true), ec);
            if (ec) {
                log_message("ERROR", "Set option failed: " + ec.message());
                return;
            }
    
            acceptor_.bind(endpoint, ec);
            if (ec) {
                log_message("ERROR", "Bind failed: " + ec.message());
                return;
            }
    
            acceptor_.listen(net::socket_base::max_listen_connections, ec);
            if (ec) {
                log_message("ERROR", "Listen failed: " + ec.message());
                return;
            }
        }
    
        void run() {
            do_accept();
        }
    
    private:
        void do_accept() {
            acceptor_.async_accept(
                net::make_strand(ioc_),
                beast::bind_front_handler(
                    &Listener::on_accept,
                    shared_from_this()));
        }
    
        void on_accept(beast::error_code ec, tcp::socket socket) {
            if (ec) {
                log_message("ERROR", "Accept failed: " + ec.message());
            } else {
                std::make_shared<Session>(
                    std::move(socket),
                    std::ref(graph_data_),
                    std::ref(running_)
                )->run();
            }
    
            if (running_) {
                do_accept();
            }
        }
    };

// Request handling
void handle_request(const http::request<http::string_body>& req, 
    http::response<http::string_body>& res,
    const GraphData& g_data) {
// Set up response defaults
res.version(req.version());
res.keep_alive(req.keep_alive());
res.set(http::field::server, "Beast");

// Only handle GET requests
if (req.method() != http::verb::get) {
res.result(http::status::method_not_allowed);
res.set(http::field::content_type, "text/plain");
res.body() = "Method not allowed\n";
return;
}

// Parse query parameters from target
string target = string(req.target());
size_t pos = target.find('?');
if (pos == string::npos) {
res.result(http::status::bad_request);
res.set(http::field::content_type, "text/plain");
res.body() = "Missing query parameters\n";
return;
}

string path = target.substr(0, pos);
string query = target.substr(pos + 1);

// Parse start and end nodes
int start = -1, end = -1;
stringstream query_stream(query);
string param;
while (getline(query_stream, param, '&')) {
if (param.find("start=") == 0) {
start = stoi(param.substr(6));
} else if (param.find("end=") == 0) {
end = stoi(param.substr(4));
}
}

if (start == -1 || end == -1) {
res.result(http::status::bad_request);
res.set(http::field::content_type, "text/plain");
res.body() = "Invalid or missing start/end parameters\n";
return;
}

// Process the path finding request
auto start_time = chrono::high_resolution_clock::now();
vector<int> distances(g_data.adjacency.size(), numeric_limits<int>::max());

auto result = biDirectionalDijkstra(g_data, start, end, distances);

auto end_time = chrono::high_resolution_clock::now();
auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();

if (!result) {
res.result(http::status::not_found);
res.set(http::field::content_type, "text/plain");
res.body() = "No path found\n";
return;
}

// Calculate total distance
int total_dist = distances[end];

// Format response based on Accept header
string accept = string(req.at(http::field::accept));
string response;

if (accept.find("application/xml") != string::npos) {
res.set(http::field::content_type, "application/xml");
response = to_xml(start, end, *result, duration, total_dist);
} else {
res.set(http::field::content_type, "application/json");
response = to_json(start, end, *result, duration, total_dist);
}

res.result(http::status::ok);
res.body() = response;
}

// Main function
#ifdef SERVER_MODE
int main() {
cout << SEPARATOR << endl;
log_message("STARTUP", "Initializing server...", true);

try {
// Load graph data
std::string binary_file_path = "USA-roads.bin";
std::string csv_file_path = "USA-roads.csv";

log_message("STARTUP", "Loading graph data...", true);
GraphData g_data = load_graph_data_from_binary(binary_file_path, csv_file_path);
log_message("STARTUP", "Graph data loaded successfully", true);

// The io_context is required for all I/O
net::io_context ioc{1};
std::atomic<bool> running{true};

// Create and launch signal handler
net::signal_set signals(ioc, SIGINT, SIGTERM);
signals.async_wait([&](beast::error_code const&, int) {
running = false;
ioc.stop();
log_message("SERVER", "Received shutdown signal, stopping server...", true);
});

// Create endpoint and listener
auto const address = net::ip::make_address("0.0.0.0");
auto const port = static_cast<unsigned short>(8080);
auto const endpoint = tcp::endpoint{address, port};

// Create and launch the listener
std::make_shared<Listener>(
ioc,
endpoint,
std::ref(g_data),
std::ref(running)
)->run();

log_message("SERVER", "Listening on 0.0.0.0:8080", true);
cout << SEPARATOR << endl;

// Run the I/O service
ioc.run();

log_message("SERVER", "Server stopped gracefully", true);
return 0;
}
catch(const std::exception& e) {
log_message("ERROR", string("Fatal error: ") + e.what());
return 1;
}
}
#endif