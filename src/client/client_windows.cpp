#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm> // For std::all_of
#include <sstream>   // For std::stringstream

using namespace std;

// Function to execute a curl command in a new terminal
void execute_curl(const string& server, const string& path, const string& accept_header) {
    // Construct the curl command
    string curl_command = "curl -X GET \"http://" + server + ":8080" + path + "\" -H \"Accept: " + accept_header + "\"";

    // Construct the command to open a new terminal and run curl
    string full_command = "start cmd /k " + curl_command;

    // Execute the command
    int result = system(full_command.c_str());

    if (result != 0) {
        cerr << "\033[1;31mError: Failed to execute curl command\033[0m\n";
    }
}

// Print the header
void print_header() {
    cout << "\033[1;35m========================================\033[0m\n";
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
void print_footer() {
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

        // Execute the curl command in a new terminal
        execute_curl("localhost", path.str(), format);

        cout << "\n\033[1;33mDo you want to find another path? (y/N): \033[0m";
        string repeat_input;
        getline(cin, repeat_input);
        repeat_choice = repeat_input.empty() ? 'n' : tolower(repeat_input[0]);
    } while (repeat_choice == 'y');

    // Print the footer
    print_footer();

    return 0;
}