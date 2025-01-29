#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <memory>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
using tcp = net::ip::tcp;
using namespace std;

// Function to handle the response from the server
void handle_response(const string& response) {
    cout << "Response from server:\n" << response << endl;
}

// Function to send a request using Boost.Beast with SSL
void send_request(const string& server, const string& path, const string& accept_header) {
    try {
        // Create the IO context
        net::io_context ioc;

        // Create the SSL context
        ssl::context ctx(ssl::context::tlsv12_client);
        ctx.set_verify_mode(ssl::verify_none); // Note: In production, you should verify certificates

        // Create the resolver
        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve(server, "443");

        // Create and connect the SSL stream
        beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

        // Set SNI Hostname (many hosts need this to handshake successfully)
        SSL_set_tlsext_host_name(stream.native_handle(), server.c_str());
        
        // Connect to the server
        beast::get_lowest_layer(stream).connect(results);

        // Perform the SSL handshake
        stream.handshake(ssl::stream_base::client);

        // Set up the HTTP GET request
        http::request<http::empty_body> req{http::verb::get, path, 11};
        req.set(http::field::host, server);
        req.set(http::field::accept, accept_header);
        req.set(http::field::user_agent, "Boost Beast Client");

        // Send the HTTP request
        http::write(stream, req);

        // Receive the response
        beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(stream, buffer, res);

        // Handle the response
        string response_content = boost::beast::buffers_to_string(res.body().data());
        handle_response(response_content);

        // Gracefully close the stream
        beast::error_code ec;
        stream.shutdown(ec);
        if(ec && ec != net::error::eof)
            throw beast::system_error{ec};

    } catch (const beast::system_error& e) {
        cerr << "Error: " << e.what() << endl;
    } catch (const std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
}

int main() {
    char repeat_choice;
    do {
        // Prompt user for start and end nodes
        int start_node, end_node;
        cout << "Enter the start node: ";
        cin >> start_node;
        cout << "Enter the end node: ";
        cin >> end_node;

        // Prompt user for the response format
        int choice;
        cout << "Choose response format (1 for JSON, 2 for XML): ";
        cin >> choice;
        string format = (choice == 1) ? "application/json" : "application/xml";

        // Construct the URL with query parameters
        stringstream path;
        path << "/path?start=" << start_node << "&end=" << end_node;

        // Server info - ngrok URL (without https://)
        string server = "873d-90-107-137-222.ngrok-free.app";

        // Send the request
        send_request(server, path.str(), format);

        // Ask user if they want to calculate another path
        cout << "\nDo you want to calculate another path? (y for yes, n for no): ";
        cin >> repeat_choice;

    } while (repeat_choice == 'y' || repeat_choice == 'Y');

    cout << "Exiting program." << endl;
    return 0;
}