#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <vector>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

int main() {
    try {
        net::io_context ioc;
        net::ip::tcp::acceptor acceptor(ioc, {net::ip::tcp::v4(), 8080});
        net::ip::tcp::socket socket(ioc);

        std::cout << "Server listening on port 8080...\n";

        acceptor.accept(socket);

        beast::flat_buffer buffer;
        http::request<http::string_body> req;
        http::read(socket, buffer, req);

        std::cout << "Received request: " << req << "\n";

        http::response<http::string_body> res{
            http::status::ok, req.version()};
        res.set(http::field::server, "Boost.Beast");
        res.set(http::field::content_type, "text/plain");
        res.body() = "Hello World!";
        res.prepare_payload();

        http::write(socket, res);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
