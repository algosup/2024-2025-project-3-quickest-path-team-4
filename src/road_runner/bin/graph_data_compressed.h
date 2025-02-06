#ifndef GRAPH_DATA_H
#define GRAPH_DATA_H

#include <vector>
#include <unordered_map>
#include <limits>
#include <iostream>  // Add this line

struct Coordinate {
    int x, y;
};

struct graph_data {
    std::vector<std::vector<std::pair<int, int>>> adjacency;
    std::vector<int> node_degrees;
    int min_edge_weight = std::numeric_limits<int>::max();
    std::vector<Coordinate> coordinates;

    explicit graph_data(size_t size = 0) : adjacency(size), node_degrees(size, 0), coordinates(size) {}

    void add_edge(int from, int to, int weight) {
        if (from >= adjacency.size()) {
            adjacency.resize(from + 1);
            node_degrees.resize(from + 1, 0);
            coordinates.resize(from + 1);
        }
        if (to >= adjacency.size()) {
            adjacency.resize(to + 1);
            node_degrees.resize(to + 1, 0);
            coordinates.resize(to + 1);
        }
        adjacency[from].emplace_back(to, weight);
        node_degrees[from]++;
        node_degrees[to]++;

        if (weight < min_edge_weight) {
            min_edge_weight = weight;
        }
    }

    void print_contents() const {
        std::cout << "Graph Data:\n";
        std::cout << "Adjacency List:\n";
        for (size_t i = 0; i < adjacency.size(); ++i) {
            std::cout << "Node " << i << " -> ";
            for (const auto& [neighbor, cost] : adjacency[i]) {
                std::cout << "(" << neighbor << ", " << cost << ") ";
            }
            std::cout << "\n";
        }
        std::cout << "Minimum edge weight: " << min_edge_weight << std::endl;
    }
};

#endif // GRAPH_DATA_H