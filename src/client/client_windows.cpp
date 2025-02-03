#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#ifdef _WIN32
    #include <windows.h>
#endif

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;
using namespace std;

#ifdef _WIN32
void initialize_windows_console() {
    // Enable ANSI escape sequences for Windows console
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

// Function to clear input buffer
void clear_input_buffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to handle the response from the server
void handle_response(const string &response) {
    cout << "\n\033[1;36mResponse from server:\033[0m\n";  // Cyan color for the header
    cout << "\033[1;32m" << response << "\033[0m\n";       // Green color for the response
}

// Function to send a request using Boost.Beast (plain HTTP)
void send_request(const string &server, const string &path, const string &accept_header) {
    try {
        // Create the IO context
        net::io_context ioc;

        // Create the resolver
        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve(server, "8080");

        // Create and connect the TCP stream
        beast::tcp_stream stream(ioc);

        // Connect to the server
        stream.connect(results);

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
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);
        if (ec && ec != beast::errc::not_connected)
            throw beast::system_error{ec};
    }
    catch (const beast::system_error &e) {
        cerr << "\033[1;31mError: " << e.what() << "\033[0m\n";  // Red color for errors
    }
    catch (const std::exception &e) {
        cerr << "\033[1;31mException: " << e.what() << "\033[0m\n";  // Red color for exceptions
    }
}

void print_header() {
    cout << "\033[1;35m========================================\033[0m\n";  // Magenta color for the header
    cout << "\033[1;35m    ROADRUNNER - Client   \033[0m\n";
    cout << "\033[1;35m========================================\033[0m\n";
}

void print_footer() {
    cout << "\033[1;35m========================================\033[0m\n";
    cout << "\033[1;35m Thank you for using the ROADRUNNER! \033[0m\n";
    cout << "\033[1;35m========================================\033[0m\n";
}

bool get_valid_number(int &number, const string &prompt) {
    string input;
    cout << "\033[1;33m" << prompt << "\033[0m";
    getline(cin, input);
    
    try {
        number = stoi(input);
        return true;
    } catch (...) {
        cout << "\033[1;31mInvalid input. Please enter a valid number.\033[0m\n";
        return false;
    }
}

int main() {
    #ifdef _WIN32
        initialize_windows_console();
    #endif

    string repeat_choice;
    do {
        // Print the header
        print_header();

        // Prompt user for start and end nodes
        int start_node, end_node;
        
        while (!get_valid_number(start_node, "Enter the start node: ")) {}
        while (!get_valid_number(end_node, "Enter the end node: ")) {}

        // Prompt user for the response format
        cout << "\033[1;33mChoose response format:\033[0m\n";
        cout << "1. JSON\n";
        cout << "2. XML\n";
        
        int choice;
        do {
            if (!get_valid_number(choice, "Enter your choice (1 or 2): ")) {
                continue;
            }
        } while (choice != 1 && choice != 2);

        string format = (choice == 1) ? "application/json" : "application/xml";

        // Construct the URL with query parameters
        stringstream path;
        path << "/path?start=" << start_node << "&end=" << end_node;

        // Server info - localhost
        string server = "localhost";

        // Send the request
        cout << "\n\033[1;34mSending request to server...\033[0m\n";  // Blue color for status messages
        send_request(server, path.str(), format);

        // Ask user if they want to calculate another path
        cout << "\n\033[1;33mDo you want to calculate another path? (y/n): \033[0m";
        getline(cin, repeat_choice);
        
    } while (repeat_choice == "y" || repeat_choice == "Y");

    // Print the footer
    print_footer();

    return 0;
}