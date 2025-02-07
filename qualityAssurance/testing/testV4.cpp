#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <limits>
#include <tuple>  // Add this for std::tuple
#include "V4/graph_data.h"
#include "V4/loading.h"
#include "V4/preprocess.h"
#include "V4/Bidirectional_Astar.h"
#include "V4/save_load_binary.h"

using namespace std;

// Function to read the test cases from the CSV file
vector<std::tuple<std::string, int, int>> read_test_cases(const string& file_path) {
    vector<std::tuple<std::string, int, int>> test_cases;
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open test cases file: " << file_path << endl;
        return test_cases;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, start_str, end_str;
        getline(ss, id, ',');
        getline(ss, start_str, ',');
        getline(ss, end_str, ',');

        int start = stoi(start_str);
        int end = stoi(end_str);
        test_cases.emplace_back(id, start, end);
    }

    file.close();
    return test_cases;
}

// Function to write results to a markdown file
void write_results_to_markdown(const string& file_path, const vector<std::tuple<std::string, int, double>>& results) {
    ofstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open markdown file for writing: " << file_path << endl;
        return;
    }

    // Write the markdown table header
    file << "| ID | Number of Nodes | Execution Time (ms) |\n";
    file << "|----|-----------------|---------------------|\n";

    // Write each result as a row in the table
    for (const auto& result : results) {
        file << "| " << get<0>(result) << " | " << get<1>(result) << " | " << get<2>(result) << " |\n";
    }

    file.close();
}

int main() {
    string graph_file_path = "../../src/server/USA-roads.csv";
    string compressed_paths_file = "./V4/compressed_paths.bin";
    string test_cases_file = "./testFile/testCases.csv";
    string output_markdown_file = "./testResults/summaryV4.md";

    // Load the graph data
    graph_data g_data = load_graph_data(graph_file_path);

    // Load compressed paths from binary file
    unordered_map<int, unordered_map<int, path_info> > compressed_paths;
    if (!load_compressed_paths_binary(compressed_paths_file, compressed_paths)) {
        cerr << "Failed to load compressed paths from binary file. Proceeding without precomputed paths." << endl;
    }

    // Preprocess the graph (only once at the beginning)
    unordered_map<int, int> single_neighbors;
    preprocess(&g_data, &single_neighbors, compressed_paths);

    // Read test cases from the CSV file
    vector<std::tuple<std::string, int, int>> test_cases = read_test_cases(test_cases_file);
    if (test_cases.empty()) {
        cerr << "No test cases found. Exiting." << endl;
        return 1;
    }

    // Vector to store results (ID, number of nodes, execution time)
    vector<std::tuple<std::string, int, double>> results;

    // Process each test case
    for (const auto& test_case : test_cases) {
        string id = get<0>(test_case);
        int start = get<1>(test_case);
        int end = get<2>(test_case);

        vector<int> distances(g_data.adjacency.size(), numeric_limits<int>::max());
        distances[start] = 0;

        are_extremities_singles are_they;
        check_single_start_or_end(&start, &end, &single_neighbors, &are_they);

        // Measure execution time for finding the shortest path
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        auto result = bidirectional_astar(g_data, start, end, distances);
        chrono::steady_clock::time_point stop = chrono::steady_clock::now();

        double execution_time = chrono::duration_cast<chrono::milliseconds>(stop - begin).count();

        // Handle the result
        int num_nodes = 0;
        if (result.has_value()) {
            if (are_they.is_start_single) {
                result.value().insert(result.value().begin(), start);
            }
            if (are_they.is_end_single) {
                result.value().push_back(end);
            }
            num_nodes = result.value().size();
        }

        // Record the result
        results.emplace_back(id, num_nodes, execution_time);
    }

    // Write results to the markdown file
    write_results_to_markdown(output_markdown_file, results);

    cout << "Test cases processed. Results written to " << output_markdown_file << endl;
    return 0;
}