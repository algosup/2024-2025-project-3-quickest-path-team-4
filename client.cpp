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
    cout << "\n\033[1;36mResponse from server:\033[0m\n"; // Cyan color for the header
    cout << "\033[1;32m" << response << "\033[0m\n";     // Green color for the response
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
        cerr << "\033[1;31mError: " << e.what() << "\033[0m\n"; // Red color for errors
    } catch (const std::exception& e) {
        cerr << "\033[1;31mException: " << e.what() << "\033[0m\n"; // Red color for exceptions
    }
}

void print_header() {
    cout << "\033[1;35m========================================\033[0m\n"; // Magenta color for the header
    cout << "\033[1;35m    ROADRUNNER - Client   \033[0m\n";
    cout << "\033[1;35m========================================\033[0m\n";
}

void print_footer() {
    cout << "\033[1;35m========================================\033[0m\n";
    cout << "\033[1;35m Thank you for using the ROADRUNNER! \033[0m\n";
    cout << "\033[1;35m========================================\033[0m\n";
}

int main() {
    char repeat_choice;
    do {
        // Print the header
        print_header();

        // Prompt user for start and end nodes
        int start_node, end_node;
        cout << "\033[1;33mEnter the start node: \033[0m"; // Yellow color for prompts
        cin >> start_node;
        cout << "\033[1;33mEnter the end node: \033[0m";
        cin >> end_node;

        // Prompt user for the response format
        int choice;
        cout << "\033[1;33mChoose response format (1 for JSON, 2 for XML): \033[0m";
        cin >> choice;
        string format = (choice == 1) ? "application/json" : "application/xml";

        // Construct the URL with query parameters
        stringstream path;
        path << "/path?start=" << start_node << "&end=" << end_node;

        // Server info - ngrok URL (without https://)
        string server = "c1dd-176-149-154-211.ngrok-free.app";

        // Send the request
        cout << "\n\033[1;34mSending request to server...\033[0m\n"; // Blue color for status messages
        send_request(server, path.str(), format);

        // Ask user if they want to calculate another path
        cout << "\n\033[1;33mDo you want to calculate another path? (y for yes, n for no): \033[0m";
        cin >> repeat_choice;

    } while (repeat_choice == 'y' || repeat_choice == 'Y');

    // Print the footer
    print_footer();

    return 0;
}