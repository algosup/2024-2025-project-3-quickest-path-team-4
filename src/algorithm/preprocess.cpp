#include "graph_data.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <queue>

using namespace std;

struct are_extremities_singles {
    bool is_start_single = false;
    bool is_end_single = false;
};

struct path_info {
    vector<int> intermediate_nodes;
    int total_distance;
};

// Global map to store compressed path information
static unordered_map<int, unordered_map<int, path_info>> compressed_paths;

// Helper function to get the full path between two nodes
vector<int> get_full_path(int start, int end) {
    auto start_it = compressed_paths.find(start);
    if (start_it != compressed_paths.end()) {
        auto end_it = start_it->second.find(end);
        if (end_it != start_it->second.end()) {
            vector<int> full_path = {start};
            full_path.insert(full_path.end(), 
                           end_it->second.intermediate_nodes.begin(),
                           end_it->second.intermediate_nodes.end());
            full_path.push_back(end);
            return full_path;
        }
    }
    return {start, end};
}

// Helper function to compress paths
void compress_path(graph_data* graph, int start_node) {
    if (start_node >= graph->adjacency.size() || graph->adjacency[start_node].size() != 1) {
        return;
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
        
        // Store the compressed path information
        compressed_paths[start_node][end_node] = {
            intermediate,
            total_distance
        };

        // Update the graph
        if (current_node != start_node) {  // Avoid self-loops
            // Add direct edge
            graph->adjacency[start_node].clear();
            graph->adjacency[start_node].emplace_back(current_node, total_distance);

            // Remove intermediate nodes from main graph
            for (size_t i = 1; i < path.size() - 1; ++i) {
                graph->adjacency[path[i]].clear();
            }
        }
    }
}

void preprocess(graph_data* graph, unordered_map<int, int>* single_neighbors) {
    // Clear any previous compressed paths
    compressed_paths.clear();
    
    // First pass: identify all nodes that can be compressed
    vector<int> compression_candidates;
    for (size_t i = 0; i < graph->adjacency.size(); ++i) {
        if (graph->adjacency[i].size() == 1) {
            compression_candidates.push_back(i);
        }
    }

    // Second pass: compress paths
    for (int start_node : compression_candidates) {
        compress_path(graph, start_node);
    }

    // Final pass: identify remaining single neighbors
    for (size_t i = 0; i < graph->adjacency.size(); ++i) {
        if (graph->adjacency[i].size() == 1) {
            (*single_neighbors)[i] = graph->adjacency[i][0].first;
        }
    }

    // Print statistics
    cout << "Compressed paths count: " << compressed_paths.size() << endl;
    cout << "Single neighbors count: " << single_neighbors->size() << endl;
}

// Helper function to expand a compressed path segment
vector<int> expand_path_segment(const vector<int>& path) {
    vector<int> expanded_path;
    
    for (size_t i = 0; i < path.size() - 1; ++i) {
        int current = path[i];
        int next = path[i + 1];
        
        expanded_path.push_back(current);
        
        // Check if this edge is compressed
        auto full_segment = get_full_path(current, next);
        if (full_segment.size() > 2) {
            // Add intermediate nodes (excluding start and end)
            expanded_path.insert(expanded_path.end(),
                               full_segment.begin() + 1,
                               full_segment.end() - 1);
        }
    }
    
    // Add the last node
    if (!path.empty()) {
        expanded_path.push_back(path.back());
    }
    
    return expanded_path;
}

// Modified check function to handle compressed paths
void check_single_start_or_end(int* start, int* end, 
                             unordered_map<int, int>* single_neighbors, 
                             are_extremities_singles* yes) {
    // Handle start node
    if (auto it = single_neighbors->find(*start); it != single_neighbors->end()) {
        cout << "Start node is a single neighbor: " << *start << " -> " << it->second << endl;
        *start = it->second;
        yes->is_start_single = true;
    }

    // Handle end node
    if (auto it = single_neighbors->find(*end); it != single_neighbors->end()) {
        cout << "End node is a single neighbor: " << *end << " -> " << it->second << endl;
        *end = it->second;
        yes->is_end_single = true;
    }
}