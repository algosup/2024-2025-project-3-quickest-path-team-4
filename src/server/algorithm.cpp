#include "algorithm.h"
#include <thread>
#include <future>
#include <atomic>
#include <iostream>
#include <queue>
#include <limits>

namespace {
    std::atomic<bool> found{false};
    std::atomic<int> best_distance{std::numeric_limits<int>::max()};
}

using PriorityQueue = std::priority_queue<Node, std::vector<Node>, NodeComparator>;

inline int zero_heuristic(int, int) { return 0; }

void search(const graph_data& graph, int start, int end, std::vector<bool>& visited, 
           std::vector<int>& g, std::vector<int>& parent, PriorityQueue& queue, 
           std::atomic<int>& meeting_node, const std::vector<bool>& opposite_visited) {
    
    while (!queue.empty() && !found.load(std::memory_order_acquire)) {
        Node current = queue.top();
        queue.pop();

        // Skip if vertex is visited or current path is worse than best found
        if (visited[current.vertex] || current.g >= best_distance.load(std::memory_order_relaxed)) 
            continue;
        
        visited[current.vertex] = true;

        // Check for meeting point
        if (opposite_visited[current.vertex]) {
            int total_dist = current.g;
            if (total_dist < best_distance.load(std::memory_order_relaxed)) {
                best_distance.store(total_dist, std::memory_order_release);
                meeting_node.store(current.vertex, std::memory_order_release);
                found.store(true, std::memory_order_release);
            }
            continue;
        }

        // Process neighbors
        for (const auto& [next, weight] : graph.adjacency[current.vertex]) {
            if (!visited[next]) {
                int new_g = current.g + weight;
                if (new_g < g[next]) {
                    g[next] = new_g;
                    parent[next] = current.vertex;
                    queue.push(Node(new_g + zero_heuristic(next, end), new_g, next));
                }
            }
        }
    }
}

std::optional<std::vector<int>> bidirectional_astar(const graph_data& graph, int start, int end, 
                                                   std::vector<int>& distances) {
    if (start == end) {
        distances[start] = 0;
        return std::vector<int>{start};
    }

    const size_t n = graph.adjacency.size();
    if (start >= n || end >= n) return std::nullopt;

    // Reset atomic variables
    found.store(false, std::memory_order_relaxed);
    best_distance.store(std::numeric_limits<int>::max(), std::memory_order_relaxed);

    // Initialize data structures with reserve for better performance
    std::vector<bool> visited_forward(n), visited_backward(n);
    std::vector<int> g_forward(n, std::numeric_limits<int>::max());
    std::vector<int> g_backward(n, std::numeric_limits<int>::max());
    std::vector<int> parent_forward(n, -1), parent_backward(n, -1);
    std::atomic<int> meeting_node{-1};

    g_forward[start] = 0;
    g_backward[end] = 0;

    PriorityQueue forward_queue, backward_queue;
    forward_queue.push(Node(0, 0, start));
    backward_queue.push(Node(0, 0, end));

    // Run searches in parallel
    auto future_forward = std::async(std::launch::async, [&]() {
        search(graph, start, end, visited_forward, g_forward, parent_forward, 
               forward_queue, meeting_node, visited_backward);
    });

    auto future_backward = std::async(std::launch::async, [&]() {
        search(graph, end, start, visited_backward, g_backward, parent_backward, 
               backward_queue, meeting_node, visited_forward);
    });

    future_forward.get();
    future_backward.get();

    int final_node = meeting_node.load();
    if (final_node == -1) return std::nullopt;

    // Construct path efficiently
    std::vector<int> path;
    path.reserve(n/2);  // Reasonable initial capacity

    for (int at = final_node; at != -1; at = parent_forward[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    for (int at = parent_backward[final_node]; at != -1; at = parent_backward[at]) {
        path.push_back(at);
    }

    // Update distances efficiently
    distances = std::move(g_forward);
    for (size_t i = 0; i < n; ++i) {
        distances[i] = std::min(distances[i], g_backward[i]);
    }

    return path;
}