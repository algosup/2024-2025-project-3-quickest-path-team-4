#include "preprocess.h"
#include <iostream>
#include <unordered_set>

// Helper function to compress paths
void compress_path(graph_data* graph, int start_node, unordered_set<int>& processed_nodes, const unordered_map<int, unordered_map<int, path_info>>& compressed_paths) {
    if (start_node >= graph->adjacency.size() || graph->adjacency[start_node].size() != 1) {
        return;
    }

    // Check if the start node is part of a precomputed path
    if (compressed_paths.find(start_node) != compressed_paths.end()) {
        return;  // Skip compression for precomputed paths
    }

    vector<int> path = {start_node};
    int current_node = start_node;
    int total_distance = 0;

    while (true) {
        if (current_node >= graph->adjacency.size() || graph->adjacency[current_node].size() != 1) {
            break;
        }

        int next_node = graph->adjacency[current_node][0].first;
        int edge_weight = graph->adjacency[current_node][0].second;

        // Check for cycles
        if (find(path.begin(), path.end(), next_node) != path.end()) {
            break;
        }

        total_distance += edge_weight;
        path.push_back(next_node);
        current_node = next_node;
    }

    // If we found a path of length > 2, store it
    if (path.size() > 2) {
        int end_node = path.back();

        // Store intermediate nodes
        vector<int> intermediate(path.begin() + 1, path.end() - 1);

        // Update the graph
        if (current_node != start_node) {  // Avoid self-loops
            // Add direct edge
            graph->adjacency[start_node].clear();
            graph->adjacency[start_node].emplace_back(current_node, total_distance);

            // Remove intermediate nodes from main graph
            for (size_t i = 1; i < path.size() - 1; ++i) {
                graph->adjacency[path[i]].clear();
                processed_nodes.insert(path[i]);  // Mark nodes as processed
            }
        }
    }
}

void preprocess(graph_data* graph, unordered_map<int, int>* single_neighbors, const unordered_map<int, unordered_map<int, path_info>>& compressed_paths) {
    // Clear any previous compressed paths
    unordered_set<int> processed_nodes;

    // First pass: identify all nodes that can be compressed
    vector<int> compression_candidates;
    for (size_t i = 0; i < graph->adjacency.size(); ++i) {
        if (graph->adjacency[i].size() == 1 && processed_nodes.find(i) == processed_nodes.end()) {
            compression_candidates.push_back(i);
        }
    }

    // Second pass: compress paths
    for (int start_node : compression_candidates) {
        compress_path(graph, start_node, processed_nodes, compressed_paths);
    }

    // Final pass: identify remaining single neighbors
    for (size_t i = 0; i < graph->adjacency.size(); ++i) {
        if (graph->adjacency[i].size() == 1 && processed_nodes.find(i) == processed_nodes.end()) {
            (*single_neighbors)[i] = graph->adjacency[i][0].first;
        }
    }

    // Print statistics
    cout << "Compressed paths count: " << compression_candidates.size() << endl;
    cout << "Single neighbors count: " << single_neighbors->size() << endl;
}

// Implementation of check_single_start_or_end
void check_single_start_or_end(int* start, int* end, unordered_map<int, int>* single_neighbors, are_extremities_singles* yes) {
    if (single_neighbors->find(*start) != single_neighbors->end()) {
        *start = (*single_neighbors)[*start];
        yes->is_start_single = true;
    }
    if (single_neighbors->find(*end) != single_neighbors->end()) {
        *end = (*single_neighbors)[*end];
        yes->is_end_single = true;
    }
}