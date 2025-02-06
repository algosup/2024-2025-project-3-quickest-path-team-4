#ifndef BIDIRECTIONAL_ASTAR_H
#define BIDIRECTIONAL_ASTAR_H

#include "graph_data.h"
#include <mutex>
#include <optional>
#include <vector>
#include <atomic>

// Declare the mutex as extern
extern std::mutex forward_mtx, backward_mtx;
extern std::atomic<bool> found;

// Node structure for the priority queue
struct Node {
    int f;
    int g;
    int vertex;

    Node(int f_, int g_, int v_) : f(f_), g(g_), vertex(v_) {}
};

// Use a binary heap for the priority queue
using Heap = std::vector<Node>;
auto cmp = [](const Node& a, const Node& b) { return a.f > b.f; };  // Min-heap comparator

// Zero heuristic
inline int zero_heuristic(int a, int b);

// Declare the bidirectional_astar function
std::optional<std::vector<int>> bidirectional_astar(const graph_data& graph, int start, int end, std::vector<int>& distances);

#endif // BIDIRECTIONAL_ASTAR_H