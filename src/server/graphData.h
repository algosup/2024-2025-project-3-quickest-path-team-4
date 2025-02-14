#ifndef GRAPH_DATA_H
#define GRAPH_DATA_H

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>

struct Edge {
    int from;
    int to;
    int weight;
};

struct GraphData {
    std::unordered_set<int> intersections;
    std::vector<Edge> edges;
    std::unordered_set<int> nodes_in_paths; // Nodes contained within intersection paths
    std::unordered_map<int, std::vector<std::pair<int, int>>> adjacency; // Adjacency list
};

GraphData load_graph_data_from_binary(const std::string& binary_file_path, const std::string& csv_file_path);

#endif // GRAPH_DATA_H