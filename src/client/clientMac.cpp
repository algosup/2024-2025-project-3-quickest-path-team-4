#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <memory>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;
using namespace std;

// Handle the response from the server
void handle_response(const string &response)
{
    cout << "\n\033[1;36mResponse from server:\033[0m\n"; // Cyan color for header
    
    try {
        // Check if response is JSON
        if (response[0] == '{') {
            stringstream ss(response);
            string line;
            while (getline(ss, line)) {
                // Skip the path array line
                if (line.find("\"path\":") != string::npos) {
                    while (getline(ss, line) && line.find("],") == string::npos) {
                        continue; // Skip path array contents
                    }
                    continue;
                }
                // Print relevant information
                if (line.find("start") != string::npos ||
                    line.find("end") != string::npos ||
                    line.find("number of nodes explored") != string::npos ||
                    line.find("distance") != string::npos ||
                    line.find("computation time") != string::npos) {
                    cout << "\033[1;32m" << line << "\033[0m\n";
                }
            }
        }
        // Check if response is XML
        else if (response.find("<?xml") != string::npos) {
            stringstream ss(response);
            string line;
            bool skip_path = false;
            while (getline(ss, line)) {
                // Skip path section
                if (line.find("<path>") != string::npos) {
                    skip_path = true;
                    continue;
                }
                if (line.find("</path>") != string::npos) {
                    skip_path = false;
                    continue;
                }
                // Print relevant information
                if (!skip_path && (
                    line.find("<start>") != string::npos ||
                    line.find("<end>") != string::npos ||
                    line.find("<nodes_explored>") != string::npos ||
                    line.find("<distance>") != string::npos ||
                    line.find("<computation_time>") != string::npos)) {
                    cout << "\033[1;32m" << line << "\033[0m\n";
                }
            }
        }
        else {
            // Handle other responses
            cout << "\033[1;32m" << response << "\033[0m\n";
        }
    }
    catch (const exception& e) {
        cerr << "\033[1;31mError parsing response: " << e.what() << "\033[0m\n";
    }
}

// Send a request using Boost.Beast (plain HTTP)
void send_request(const string &server, const string &path, const string &accept_header)
{
    try
    {
        // Create the IO context
        net::io_context ioc;

        // Create the resolver
        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve(server, "8080");

        // Create and connect the TCP stream
        beast::tcp_stream stream(ioc);
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
    catch (const beast::system_error &e)
    {
        cerr << "\033[1;31mError: " << e.what() << "\033[0m\n"; // Red color for errors
    }
    catch (const std::exception &e)
    {
        cerr << "\033[1;31mException: " << e.what() << "\033[0m\n"; // Red color for exceptions
    }
}

// Print the header
void print_header()
{
    cout << "\033[1;35m========================================\033[0m\n"; // Magenta color for the header
    cout << "\033[1;35m    ROADRUNNER - Client   \033[0m\n";
    cout << "\033[1;35m========================================\033[0m\n";
}

// Validate user input
bool is_valid_input(const string& input, int& value) {
    if (input.empty()) return false;
    
    // Check if input contains only digits
    if (!all_of(input.begin(), input.end(), ::isdigit)) {
        cout << "\033[1;31mError: Input must contain only numbers\033[0m\n";
        return false;
    }
    
    try {
        value = stoi(input);
        if (value < 1 || value > 23947347) {
            cout << "\033[1;31mError: Input must be between 1 and 23947347\033[0m\n";
            return false;
        }
        return true;
    } catch (const exception& e) {
        cout << "\033[1;31mError: Invalid number format\033[0m\n";
        return false;
    }
}

// Print the footer
void print_footer()
{
    cout << "\033[1;35m========================================\033[0m\n";
    cout << "\033[1;35m Thank you for using the ROADRUNNER! \033[0m\n";
    cout << "\033[1;35m========================================\033[0m\n";
}

int main() {
    char repeat_choice;
    do {
        print_header();
    
        // Prompt user for start and end nodes with validation
        int start_node, end_node;
        string input;
        bool valid_input = false;
    
        // Get valid start node
        do {
            cout << "\033[1;33mEnter the start node: \033[0m";
            getline(cin, input);
            valid_input = is_valid_input(input, start_node);
        } while (!valid_input);
    
        // Get valid end node
        do {
            cout << "\033[1;33mEnter the end node: \033[0m";
            getline(cin, input);
            valid_input = is_valid_input(input, end_node);
        } while (!valid_input);
    
        // Prompt user for the response format
        int choice;
        bool valid_choice = false;
        do {
            cout << "\033[1;33mChoose response format (1 for JSON, 2 for XML): \033[0m";
            getline(cin, input);
            if (input == "1" || input == "2") {
                choice = stoi(input);
                valid_choice = true;
            } else {
                cout << "\033[1;31mError: Please enter 1 or 2\033[0m\n";
            }
        } while (!valid_choice);
    
        string format = (choice == 1) ? "application/json" : "application/xml";
        stringstream path;
        path << "/path?start=" << start_node << "&end=" << end_node;
        send_request("localhost", path.str(), format);
        cout << "\n\033[1;33mDo you want to find another path? (y/N): \033[0m";
        string repeat_input;
        getline(cin, repeat_input);
        repeat_choice = repeat_input.empty() ? 'n' : tolower(repeat_input[0]);
    } while (repeat_choice == 'y');

    // Print the footer
    print_footer();

    return 0;
}