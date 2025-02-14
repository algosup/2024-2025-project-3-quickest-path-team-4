#ifndef BINARY_WRITER_H
#define BINARY_WRITER_H

#include <vector>
#include <unordered_set>
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
};

bool write_binary(const std::string& filename, const GraphData& graph_data);

#endif // BINARY_WRITER_H