#ifndef BIDIRECTIONAL_ASTAR_H
#define BIDIRECTIONAL_ASTAR_H

#include "graph_data.h"
#include <mutex>
#include <optional>
#include <vector>
#include <atomic>

extern std::mutex forward_mtx, backward_mtx;
extern std::atomic<bool> found;

struct Node {
    int f;
    int g;
    int vertex;

    Node(int f_, int g_, int v_) : f(f_), g(g_), vertex(v_) {}
};

using Heap = std::vector<Node>;
auto cmp = [](const Node& a, const Node& b) { return a.f > b.f; };

inline int zero_heuristic(int a, int b);

std::optional<std::vector<int>> bidirectional_astar(const graph_data& graph, int start, int end, std::vector<int>& distances);

#endif