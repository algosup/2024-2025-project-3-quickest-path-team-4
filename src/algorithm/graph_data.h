#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

struct graph_data {
    vector<vector<pair<int, int>>> adjacency;
    
    // Constructor to initialize the graph with a given size
    explicit graph_data(size_t size = 0) : adjacency(size) {}
    
    void add_edge(int from, int to, int weight) {
        if (from >= adjacency.size()) adjacency.resize(from + 1);
        if (to >= adjacency.size()) adjacency.resize(to + 1);
        adjacency[from].emplace_back(to, weight);
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
    }
};