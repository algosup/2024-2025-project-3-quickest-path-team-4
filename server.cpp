#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <optional>
#include "graph_data.h"
#include "Dijkstra.cpp"
#include "loading.cpp"
#include "preprocess.cpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

graph_data gdata = load_graph_data("USA-roads.csv");

unordered_map<int, int> single_neighbors;

void handle_request(const http::request<http::string_body>& req, http::response<http::string_body>& res) {
    // Check if the request is a GET to the "/path" route
    if (req.method() == http::verb::get && req.target().starts_with("/path")) {
        // Convert the target (string_view) to a std::string for easier manipulation
        std::string query(req.target().begin(), req.target().end());  // Explicitly create a string from string_view

        // Parse query parameters (e.g., /path?start=1&end=5)
        int start = -1, end = -1;
        std::unordered_map<std::string, std::string> params;

        // Extract query parameters
        if (query.find('?') != std::string::npos) {
            query = query.substr(query.find('?') + 1);
            std::stringstream ss(query);
            std::string token;

            while (std::getline(ss, token, '&')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string key = token.substr(0, pos);
                    std::string value = token.substr(pos + 1);
                    params[key] = value;
                }
            }

            // Extract start and end from the query parameters
            if (params.find("start") != params.end() && params.find("end") != params.end()) {
                try {
                    start = std::stoi(params["start"]);
                    end = std::stoi(params["end"]);
                } catch (const std::exception& e) {
                    res.result(http::status::bad_request);
                    res.body() = "Invalid start or end node.";
                    res.set(http::field::content_type, "text/plain");
                    res.prepare_payload();
                    return;
                }
            }
        }

        if (start == -1 || end == -1) {
            res.result(http::status::bad_request);
            res.body() = "Missing start or end node.";
            res.set(http::field::content_type, "text/plain");
            res.prepare_payload();
            return;
        }
        std::cout << start << std::endl << end << std::endl;

        are_extremities_singles are_they;

        // Distance map: node -> shortest distance from the start node
		unordered_map<int, int> distances;

		// Initialize distances to infinity and start node to 0
		for (const auto &[node, _] : gdata.adjacency)
		{
			distances[node] = numeric_limits<int>::max();
		}

        int true_start = start;
		int true_end = end;

        distances[start] = 0;

        check_single_start_or_end(&start, &end, &single_neighbors, &are_they);
  
        // Run Dijkstra's algorithm
        auto result = bidirectional_dijkstra(gdata, start, end, &distances);

        // Prepare the response
        res.result(http::status::ok);
        if (result.has_value()){
            std::stringstream path;
			if (are_they.is_start_single){
				result.value().insert(result.value().begin(), start);
			}
			if (are_they.is_end_single){
				result.value().push_back(end);
			}
			for (int node : result.value()){
				path << node << " ";
				}
            res.body() = "Shortest path from " + std::to_string(start) + " to " + std::to_string(end) + ": " + path.str();
		} else {
            res.body() = "No path found from " + std::to_string(start) + " to " + std::to_string(end);
        }
        res.set(http::field::content_type, "text/plain");
        res.prepare_payload();
    } else {
        // Handle invalid route
        res.result(http::status::not_found);
        res.body() = "Route not found.";
        res.set(http::field::content_type, "text/plain");
        res.prepare_payload();
    }
}

void do_session(tcp::socket socket) {
    try {
        beast::flat_buffer buffer;

        // Read an HTTP request
        http::request<http::string_body> req;
        http::read(socket, buffer, req);

        std::cout << req << std::endl;

        // Prepare an HTTP response
        http::response<http::string_body> res;

        // Handle the request
        handle_request(req, res);

        // Write the response back to the client
        http::write(socket, res);
    } catch (std::exception& e) {
        std::cerr << "Session error: " << e.what() << std::endl;
    }
}

int main() {

    preprocess(&gdata, &single_neighbors);

    try {
        net::io_context ioc;

        // Create an endpoint for listening on port 8080
        tcp::acceptor acceptor{ioc, tcp::endpoint(tcp::v4(), 8080)};
        acceptor.set_option(net::socket_base::reuse_address(true));

        std::cout << "Server is listening on 8080" << std::endl;

        while (true) {
            // Accept a new connection
            tcp::socket socket(ioc);
            acceptor.accept(socket);

            // Handle the session
            do_session(std::move(socket));
        }

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
