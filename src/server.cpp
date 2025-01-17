#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

std::string read_file(const std::string &file_path)
{
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + file_path);
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

int main()
{
    try
    {
        const std::string file_path = "USA-roads.csv";

        net::io_context ioc;
        net::ip::tcp::acceptor acceptor(ioc, {net::ip::tcp::v4(), 8080});
        acceptor.set_option(net::socket_base::reuse_address(true));

        std::cout << "Server listening on port 8080...\n";

        while (true)
        {
            // Create a new socket for each connection
            net::ip::tcp::socket socket(ioc);

            // Accept a connection
            acceptor.accept(socket);

            try
            {
                // Read the request
                beast::flat_buffer buffer;
                http::request<http::string_body> req;
                http::read(socket, buffer, req);

                std::cout << "Received request: " << req << "\n";

                // Prepare the response
                std::string file_content = read_file(file_path);

                http::response<http::string_body> res{
                    http::status::ok, req.version()};
                res.set(http::field::server, "Boost.Beast");
                res.set(http::field::content_type, "text/csv");
                res.body() = file_content;
                res.prepare_payload();

                // Send the response
                http::write(socket, res);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error handling request: " << e.what() << "\n";
            }

            // Shutdown and close the socket after handling the request
            beast::error_code ec;
            socket.shutdown(net::ip::tcp::socket::shutdown_send, ec);
            if (ec && ec != beast::errc::not_connected)
            {
                std::cerr << "Socket shutdown error: " << ec.message() << "\n";
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

