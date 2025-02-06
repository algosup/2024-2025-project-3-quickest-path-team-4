#include "Bidirectional_Astar.h"
#include <thread>
#include <future>
#include <queue>
#include <atomic>
#include <iostream>

std::atomic<bool> found(false);

// Comparator for priority queue
struct NodeComparator {
    bool operator()(const Node& a, const Node& b) const {
        return a.f > b.f; // Min-heap
    }
};

// Define a priority queue for min-heap
using PriorityQueue = std::priority_queue<Node, std::vector<Node>, NodeComparator>;

inline int zero_heuristic(int a, int b) {
    return 0; // No coordinate data, so use zero heuristic
}

void search(const graph_data& graph, int start, int end, std::vector<bool>& visited, std::vector<int>& g, std::vector<int>& parent, PriorityQueue* queue, std::atomic<int>& meeting_node, std::vector<int>& explored_nodes, const std::vector<bool>& opposite_visited) {
    while (!queue->empty() && !found.load(std::memory_order_relaxed)) {
        Node node = queue->top();
        queue->pop();

        int curr = node.vertex;
        if (visited[curr]) continue;
        visited[curr] = true;
        explored_nodes.push_back(curr);

        if (opposite_visited[curr]) {
            meeting_node.store(curr, std::memory_order_relaxed);
            found.store(true, std::memory_order_relaxed);
            return;
        }

        for (const auto& [next, weight] : graph.adjacency[curr]) {
            if (visited[next]) continue;

            int new_g = node.g + weight;
            if (new_g < g[next]) {
                g[next] = new_g;
                parent[next] = curr;
                queue->push(Node(new_g + zero_heuristic(next, end), new_g, next));
            }
        }
    }
}

std::optional<std::vector<int>> bidirectional_astar(const graph_data& graph, int start, int end, std::vector<int>& distances) {
    if (start == end) {
        distances[start] = 0;
        return std::vector<int>{start};
    }

    const size_t n = graph.adjacency.size();
    std::vector<bool> visited_forward(n, false), visited_backward(n, false);
    std::vector<int> g_forward(n, std::numeric_limits<int>::max());
    std::vector<int> g_backward(n, std::numeric_limits<int>::max());
    std::vector<int> parent_forward(n, -1), parent_backward(n, -1);
    std::atomic<int> meeting_node(-1);
    std::vector<int> explored_forward, explored_backward;

    g_forward[start] = 0;
    g_backward[end] = 0;

    PriorityQueue forward_queue, backward_queue;
    forward_queue.push(Node(zero_heuristic(start, end), 0, start));
    backward_queue.push(Node(zero_heuristic(end, start), 0, end));

    auto future_forward = std::async(std::launch::async, [&]() {
        search(graph, start, end, visited_forward, g_forward, parent_forward, &forward_queue, meeting_node, explored_forward, visited_backward);
    });
    
    auto future_backward = std::async(std::launch::async, [&]() {
        search(graph, end, start, visited_backward, g_backward, parent_backward, &backward_queue, meeting_node, explored_backward, visited_forward);
    });

    future_forward.get();
    future_backward.get();

    if (meeting_node.load() == -1) return std::nullopt;

    std::cout << "Debug: Total nodes explored forward: " << explored_forward.size() << std::endl;
    std::cout << "Debug: Total nodes explored backward: " << explored_backward.size() << std::endl;
    std::cout << "Debug: Meeting node found at " << meeting_node.load() << std::endl;

    std::vector<int> path;

    for (int at = meeting_node; at != -1; at = parent_forward[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    
    for (int at = parent_backward[meeting_node]; at != -1; at = parent_backward[at]) {
        path.push_back(at);
    }

    distances = g_forward;
    for (size_t i = 0; i < n; ++i) {
        if (g_backward[i] < distances[i]) {
            distances[i] = g_backward[i];
        }
    }

    return path;
}

// 9489093 → 22377087 : 13323 Nodes