#include "csv_parser.h"
#include "binary_writer.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool parse_csv(const std::string& file_path, GraphData& graph_data) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open CSV file: " << file_path << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        int from, to, weight;
        if (ss >> from >> to >> weight) {
            graph_data.edges.push_back({from, to, weight});
            graph_data.intersections.insert(from);
            graph_data.intersections.insert(to);
            graph_data.nodes_in_paths.insert(from);
            graph_data.nodes_in_paths.insert(to);
        }
    }

    file.close();
    return true;
}