#include "graphData.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

graph_data load_graph_data(const string &file_path) {
    ifstream file_stream(file_path);
    if (!file_stream.is_open()) {
        cerr << "Error: Could not open file: " << file_path << endl;
        return graph_data();  // Explicitly construct the graph_data object
    }

    graph_data g_data;
    string line_data;
    while (getline(file_stream, line_data)) {
        if (line_data.empty()) continue;

        stringstream line_stream(line_data);
        string val_a, val_b, val_time;

        // Read the values from the CSV
        if (!getline(line_stream, val_a, ',') ||
            !getline(line_stream, val_b, ',') ||
            !getline(line_stream, val_time, ',')) {
            cerr << "[WARNING] Malformed line: " << line_data << endl;
            continue;
        }

        int node_a, node_b, time_cost;
        try {
            node_a = stoi(val_a);
            node_b = stoi(val_b);
            time_cost = stoi(val_time);
        } catch (const exception &e) {
            cerr << "[WARNING] Invalid data on line: " << line_data << " (" << e.what() << ")\n";
            continue;
        }

        // Update the adjacency list
        g_data.add_edge(node_a, node_b, time_cost);
        g_data.add_edge(node_b, node_a, time_cost);
    }
    file_stream.close();
    return g_data;
}