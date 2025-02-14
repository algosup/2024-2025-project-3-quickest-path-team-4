#include "graphData.h"
#include "algorithm.h"
#include <queue>
#include <limits>
#include <unordered_set>
#include <vector>
#include <optional>
#include <algorithm>
#include <iostream>
#include <atomic>
#include <thread>
#include <future>

struct Node {
    int id;
    int distance;
};

struct NodeComparator {
    bool operator()(const Node& a, const Node& b) const {
        return a.distance > b.distance;
    }
};

using PriorityQueue = std::priority_queue<Node, std::vector<Node>, NodeComparator>;

namespace {
    std::atomic<bool> found{false};
    std::atomic<int> best_distance{std::numeric_limits<int>::max()};
}

inline int zero_heuristic(int, int) { return 0; }

void search(const GraphData& graph, int start, int end, std::vector<bool>& visited, 
    std::vector<int>& g, std::vector<int>& parent, PriorityQueue& queue, 
    std::atomic<int>& meeting_node, const std::vector<bool>& opposite_visited, 
    const std::unordered_set<int>& intersections, const std::unordered_set<int>& nodes_in_paths) {

while (!queue.empty() && !found.load(std::memory_order_acquire)) {
 Node current = queue.top();
 queue.pop();

 // Skip if current path is worse than best found
 if (current.distance >= best_distance.load(std::memory_order_relaxed)) {
     continue;
 }

 // Check for meeting point before marking as visited
 if (opposite_visited[current.id]) {
     int total_dist = current.distance;
     if (total_dist < best_distance.load(std::memory_order_relaxed)) {
         best_distance.store(total_dist, std::memory_order_release);
         meeting_node.store(current.id, std::memory_order_release);
         found.store(true, std::memory_order_release);
         std::cout << "Meeting point found at node: " << current.id << " with total distance: " << total_dist << std::endl;
         return;
     }
 }

 if (visited[current.id]) {
     continue;
 }
 
 visited[current.id] = true;
 g[current.id] = current.distance;

 // First priority: process nodes in paths if current node is in a path
 if (nodes_in_paths.count(current.id)) {
     for (const auto& [next, weight] : graph.adjacency.at(current.id)) {
         if (nodes_in_paths.count(next) && !visited[next]) {
             int new_g = current.distance + weight;
             if (new_g < g[next]) {
                 g[next] = new_g;
                 parent[next] = current.id;
                 queue.push(Node{next, new_g});
             }
         }
     }
 }

 // Second priority: process intersections if current node is an intersection
 if (intersections.count(current.id)) {
     for (const auto& [next, weight] : graph.adjacency.at(current.id)) {
         if (intersections.count(next) && !visited[next]) {
             int new_g = current.distance + weight;
             if (new_g < g[next]) {
                 g[next] = new_g;
                 parent[next] = current.id;
                 queue.push(Node{next, new_g});
             }
         }
     }
 }

 // Process all remaining neighbors
 for (const auto& [next, weight] : graph.adjacency.at(current.id)) {
     if (!visited[next]) {
         int new_g = current.distance + weight;
         if (new_g < g[next]) {
             g[next] = new_g;
             parent[next] = current.id;
             queue.push(Node{next, new_g});
         }
     }
 }
}
}

std::optional<std::vector<int>> biDirectionalDijkstra(const GraphData& graph, int start, int end, std::vector<int>& distances) {
    if (start == end) {
        distances[start] = 0;
        return std::vector<int>{start};
    }

    // Reset atomic variables
    found.store(false, std::memory_order_relaxed);
    best_distance.store(std::numeric_limits<int>::max(), std::memory_order_relaxed);

    // Initialize atomic meeting node
    std::atomic<int> meeting_node{-1};

    // Get the size for vectors
    const size_t n = std::max_element(graph.adjacency.begin(), graph.adjacency.end(),
        [](const auto& a, const auto& b) { return a.first < b.first; })->first + 1;

    // Initialize vectors with the correct size
    std::vector<bool> visited_forward(n), visited_backward(n);
    std::vector<int> g_forward(n, std::numeric_limits<int>::max());
    std::vector<int> g_backward(n, std::numeric_limits<int>::max());
    std::vector<int> parent_forward(n, -1), parent_backward(n, -1);

    g_forward[start] = 0;
    g_backward[end] = 0;

    PriorityQueue forward_queue, backward_queue;
    forward_queue.push(Node{start, 0});
    backward_queue.push(Node{end, 0});

    // Extract intersections and nodes in paths from graph_data
    std::unordered_set<int> intersections(graph.intersections.begin(), graph.intersections.end());
    std::unordered_set<int> nodes_in_paths(graph.nodes_in_paths.begin(), graph.nodes_in_paths.end());

    // Run searches in parallel
    auto future_forward = std::async(std::launch::async, [&]() {
        search(graph, start, end, visited_forward, g_forward, parent_forward, 
               forward_queue, meeting_node, visited_backward, intersections, nodes_in_paths);
    });

    auto future_backward = std::async(std::launch::async, [&]() {
        search(graph, end, start, visited_backward, g_backward, parent_backward, 
               backward_queue, meeting_node, visited_forward, intersections, nodes_in_paths);
    });

    future_forward.get();
    future_backward.get();
    int final_node = meeting_node.load();
    if (final_node == -1) {
        std::cout << "No meeting point found." << std::endl;
        return std::nullopt;
    }

    // Construct path efficiently
    std::vector<int> path;
    path.reserve(n / 2);  // Reasonable initial capacity

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