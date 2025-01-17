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

void send_file(const std::string &file_path, beast::tcp_stream &stream, http::request<http::string_body> &req)
{
    // Open the file to be sent
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + file_path);
    }

    // Prepare the response with file content
    boost::system::error_code ec;
    http::response<http::file_body> res{http::status::ok, req.version()};
    res.set(http::field::server, "Boost.Beast");
    res.set(http::field::content_type, "text/csv");

    res.body().open(file_path.c_str(), beast::file_mode::scan, ec);
    if (ec)
    {
        throw std::runtime_error("Error opening file: " + ec.message());
    }
    res.prepare_payload();

    // Send the response
    http::write(stream, res);
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
                // Convert the socket to a tcp_stream
                beast::tcp_stream stream(std::move(socket));

                // Read the request
                beast::flat_buffer buffer;
                http::request<http::string_body> req;
                http::read(stream, buffer, req);

                std::cout << "Received request: " << req << "\n";

                // Send the file
                send_file(file_path, stream, req);
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
