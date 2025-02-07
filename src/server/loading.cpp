#include "graphData.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

// Function to load graph data from a CSV file
graph_data load_graph_data(const string &file_path) {
    ifstream file_stream(file_path);  // Open the file
    if (!file_stream.is_open()) {  // Check if the file is open
        cerr << "Error: Could not open file: " << file_path << endl;
        return graph_data();  // Return an empty graph_data object if the file cannot be opened
    }

    graph_data g_data;  // Create a graph_data object to store the graph
    string line_data;  // String to hold each line of the file

    // Read the file line by line
    while (getline(file_stream, line_data)) {
        if (line_data.empty()) continue;  // Skip empty lines

        stringstream line_stream(line_data);  // Create a stringstream from the line
        string val_a, val_b, val_time;  // Variables to hold the values from the CSV

        // Read the values from the CSV
        if (!getline(line_stream, val_a, ',') ||
            !getline(line_stream, val_b, ',') ||
            !getline(line_stream, val_time, ',')) {
            cerr << "[WARNING] Malformed line: " << line_data << endl;
            continue;  // Skip malformed lines
        }

        int node_a, node_b, time_cost;  // Variables to hold the converted values
        try {
            node_a = stoi(val_a);  // Convert the first value to an integer
            node_b = stoi(val_b);  // Convert the second value to an integer
            time_cost = stoi(val_time);  // Convert the third value to an integer
        } catch (const exception &e) {
            cerr << "[WARNING] Invalid data on line: " << line_data << " (" << e.what() << ")\n";
            continue;  // Skip lines with invalid data
        }

        // Update the adjacency list
        g_data.add_edge(node_a, node_b, time_cost);  // Add the edge to the graph
        g_data.add_edge(node_b, node_a, time_cost);  // Add the reverse edge to the graph
    }

    file_stream.close();  // Close the file
    return g_data;  // Return the loaded graph data
}