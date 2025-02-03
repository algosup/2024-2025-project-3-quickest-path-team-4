#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

struct graph_data {
    // Maps each node to a unique index
    std::unordered_map<int, size_t> node_to_index;

    // Adjacency list: maps each node to its neighbors and the cost of edges
    std::unordered_map<int, std::vector<std::pair<int, int>>> adjacency;

    // Prints the contents of the graph_data
    void print_contents() const {
        std::cout << "Graph Data:\n";

        std::cout << "Nodes and their indices:\n";
        for (const auto& [node, index] : node_to_index) {
            std::cout << "Node: " << node << ", Index: " << index << "\n";
        }

        std::cout << "\nAdjacency List:\n";
        for (const auto& [node, neighbors] : adjacency) {
            std::cout << "Node " << node << " -> ";
            for (const auto& [neighbor, cost] : neighbors) {
                std::cout << "(" << neighbor << ", " << cost << ") ";
            }
            std::cout << "\n";
        }
    }
};
