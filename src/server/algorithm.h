#pragma once
#include "graphData.h"
#include <vector>
#include <optional>
#include <queue>
#include <algorithm> //Only on WINDOWS

struct Node {
    int f;
    int g;
    int vertex;
    Node(int f_ = 0, int g_ = 0, int v_ = 0) : f(f_), g(g_), vertex(v_) {}
};

struct NodeComparator {
    bool operator()(const Node& a, const Node& b) const {
        return a.f > b.f;
    }
};

// Remove compressed_paths parameter
std::optional<std::vector<int>> bidirectional_astar(
    const graph_data& graph,
    int start,
    int end,
    std::vector<int>& distances
);