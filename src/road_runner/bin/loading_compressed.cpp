#include "loading_compressed.h"
#include <fstream>  // Add this line
#include <sstream>  // Add this line
#include <iostream> // Add this line

graph_data load_graph_data(const std::string& file_path) {
    std::ifstream file_stream(file_path);
    if (!file_stream.is_open()) {
        std::cerr << "Error: Could not open file: " << file_path << std::endl;
        return graph_data();
    }

    graph_data g_data;
    std::string line_data;
    while (getline(file_stream, line_data)) {
        if (line_data.empty()) continue;

        std::stringstream line_stream(line_data);
        std::string val_a, val_b, val_time;

        // Read the values from the CSV
        if (!getline(line_stream, val_a, ',') ||
            !getline(line_stream, val_b, ',') ||
            !getline(line_stream, val_time, ',')) {
            std::cerr << "[WARNING] Malformed line: " << line_data << std::endl;
            continue;
        }

        int node_a, node_b, time_cost;
        try {
            node_a = std::stoi(val_a);
            node_b = std::stoi(val_b);
            time_cost = std::stoi(val_time);
        } catch (const std::exception& e) {
            std::cerr << "[WARNING] Invalid data on line: " << line_data << " (" << e.what() << ")\n";
            continue;
        }

        // Update the adjacency list
        g_data.add_edge(node_a, node_b, time_cost);
        g_data.add_edge(node_b, node_a, time_cost);
    }
    file_stream.close();
    return g_data;
}