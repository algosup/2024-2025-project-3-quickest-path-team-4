#ifndef BIDIRECTIONAL_ASTAR_H
#define BIDIRECTIONAL_ASTAR_H

#include "graph_data.h"
#include <mutex>
#include <optional>
#include <vector>
#include <queue>
#include <functional>

// Declare the mutex as extern
extern std::mutex mtx;

// Node structure for the priority queue
struct Node {
    int f;
    int g;
    int vertex;

    Node(int f_, int g_, int v_) : f(f_), g(g_), vertex(v_) {}
};

// Custom comparator for the priority queue
struct NodeComparator {
    bool operator()(const Node& a, const Node& b) const {
        return a.f > b.f;  // Min-heap
    }
};

using Heap = std::priority_queue<Node, std::vector<Node>, NodeComparator>;

// Declare the bidirectional_astar function
std::optional<std::vector<int>> bidirectional_astar(const graph_data& graph, int start, int end, std::vector<int>& distances, const std::vector<std::vector<int>>& landmark_distances);

#endif // BIDIRECTIONAL_ASTAR_H