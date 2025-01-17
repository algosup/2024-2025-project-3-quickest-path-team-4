#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

// Function to read the entire file content as a string
std::string read_file(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + file_path);
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

// Function to format the file content as a JSON response
std::string to_json(const std::string& file_content) {
    std::string json_response = "{\"file_content\": \"";
    // Escape double quotes in the file content
    std::string escaped_content = file_content;
    std::replace(escaped_content.begin(), escaped_content.end(), '"', '\\');
    json_response += escaped_content;
    json_response += "\"}";
    return json_response;
}

// Function to format the file content as an XML response
std::string to_xml(const std::string& file_content) {
    std::string xml_response = "<?xml version=\"1.0\"?>\n<file>\n";
    xml_response += "<content>";
    xml_response += file_content;
    xml_response += "</content>\n</file>";
    return xml_response;
}

// Function to send the file content as JSON or XML based on the Accept header
void send_response(beast::tcp_stream& stream, const std::string& file_path, http::request<http::string_body>& req) {
    // Read the raw file content
    std::string file_content = read_file(file_path);

    // Prepare the response based on the "Accept" header
    std::string accept = std::string(req[http::field::accept]);  // Convert boost::string_view to std::string

    http::response<http::string_body> res;
    if (accept == "application/json") {
        std::string json_data = to_json(file_content);
        res = http::response<http::string_body>(http::status::ok, req.version());
        res.set(http::field::server, "Boost.Beast");
        res.set(http::field::content_type, "application/json");
        res.body() = json_data;
    } else if (accept == "application/xml") {
        std::string xml_data = to_xml(file_content);
        res = http::response<http::string_body>(http::status::ok, req.version());
        res.set(http::field::server, "Boost.Beast");
        res.set(http::field::content_type, "application/xml");
        res.body() = xml_data;
    } else {
        // Default to JSON if no acceptable format is specified
        std::string json_data = to_json(file_content);
        res = http::response<http::string_body>(http::status::ok, req.version());
        res.set(http::field::server, "Boost.Beast");
        res.set(http::field::content_type, "application/json");
        res.body() = json_data;
    }

    res.prepare_payload();
    http::write(stream, res);
}

int main() {
    try {
        const std::string file_path = "USA-roads.csv";

        net::io_context ioc;
        net::ip::tcp::acceptor acceptor(ioc, {net::ip::tcp::v4(), 8080});
        acceptor.set_option(net::socket_base::reuse_address(true));

        std::cout << "Server listening on port 8080...\n";

        while (true) {
            // Create a new socket for each connection
            net::ip::tcp::socket socket(ioc);

            // Accept a connection
            acceptor.accept(socket);

            try {
                // Convert the socket to a tcp_stream
                beast::tcp_stream stream(std::move(socket));

                // Read the request
                beast::flat_buffer buffer;
                http::request<http::string_body> req;
                http::read(stream, buffer, req);

                std::cout << "Received request: " << req << "\n";

                // Send the file content as JSON or XML based on the Accept header
                send_response(stream, file_path, req);
            } catch (const std::exception& e) {
                std::cerr << "Error handling request: " << e.what() << "\n";
            }

            // Shutdown and close the socket after handling the request
            beast::error_code ec;
            socket.shutdown(net::ip::tcp::socket::shutdown_send, ec);
            if (ec && ec != beast::errc::not_connected) {
                std::cerr << "Socket shutdown error: " << ec.message() << "\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
