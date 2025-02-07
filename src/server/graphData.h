#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <limits>

using namespace std;

struct Coordinate {
    int x, y;
};

struct graph_data {
    vector<vector<pair<int, int>>> adjacency;
    vector<int> node_degrees;  // Store the degree of each node
    int min_edge_weight = numeric_limits<int>::max();  // Store the minimum edge weight
    vector<Coordinate> coordinates;  // Store coordinates for each node

    // Constructor to initialize the graph with a given size
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

        // Update minimum edge weight
        if (weight < min_edge_weight) {
            min_edge_weight = weight;
        }
    }

    // Prints the contents of the graph_data
    void print_contents() const {
        cout << "Graph Data:\n";
        cout << "Adjacency List:\n";
        for (size_t i = 0; i < adjacency.size(); ++i) {
            cout << "Node " << i << " -> ";
            for (const auto &[neighbor, cost] : adjacency[i]) {
                cout << "(" << neighbor << ", " << cost << ") ";
            }
            cout << "\n";
        }
        cout << "Minimum edge weight: " << min_edge_weight << endl;
    }
};