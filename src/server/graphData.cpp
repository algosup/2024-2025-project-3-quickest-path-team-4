#include "graphData.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

void load_additional_data_from_csv(const std::string& file_path, GraphData& g_data) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Error: Could not open CSV file: " << file_path << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        int from, to, weight;
        if (ss >> from >> to >> weight) {
            g_data.edges.push_back({from, to, weight});
            g_data.intersections.insert(from);
            g_data.intersections.insert(to);
            g_data.nodes_in_paths.insert(from);
            g_data.nodes_in_paths.insert(to);
            g_data.adjacency[from].emplace_back(to, weight);
            g_data.adjacency[to].emplace_back(from, weight); // Assuming undirected graph
        }
    }

    file.close();
}

GraphData load_graph_data_from_binary(const std::string& binary_file_path, const std::string& csv_file_path) {
    GraphData g_data;

    // Load binary data
    std::ifstream binary_file(binary_file_path, std::ios::binary);
    if (!binary_file.is_open()) {
        std::cerr << "Error: Could not open binary file: " << binary_file_path << std::endl;
        return g_data;
    }

    size_t num_intersections;
    binary_file.read(reinterpret_cast<char*>(&num_intersections), sizeof(num_intersections));
    for (size_t i = 0; i < num_intersections; ++i) {
        int intersection;
        binary_file.read(reinterpret_cast<char*>(&intersection), sizeof(intersection));
        g_data.intersections.insert(intersection);
    }

    size_t num_edges;
    binary_file.read(reinterpret_cast<char*>(&num_edges), sizeof(num_edges));
    for (size_t i = 0; i < num_edges; ++i) {
        Edge edge;
        binary_file.read(reinterpret_cast<char*>(&edge), sizeof(edge));
        g_data.edges.push_back(edge);
        g_data.adjacency[edge.from].emplace_back(edge.to, edge.weight);
        g_data.adjacency[edge.to].emplace_back(edge.from, edge.weight); // Assuming undirected graph
    }

    size_t num_nodes_in_paths;
    binary_file.read(reinterpret_cast<char*>(&num_nodes_in_paths), sizeof(num_nodes_in_paths));
    for (size_t i = 0; i < num_nodes_in_paths; ++i) {
        int node;
        binary_file.read(reinterpret_cast<char*>(&node), sizeof(node));
        g_data.nodes_in_paths.insert(node);
    }

    binary_file.close();

    // Load additional data from CSV if needed
    load_additional_data_from_csv(csv_file_path, g_data);

    return g_data;
}