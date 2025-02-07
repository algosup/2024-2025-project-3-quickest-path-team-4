#include "Bidirectional_Astar.h"
#include <thread>
#include <future>
#include <atomic>
#include <iostream>

// Ensure found is reset at the start of each function call
std::atomic<bool> found(false);

using PriorityQueue = std::priority_queue<Node, std::vector<Node>, NodeComparator>;

inline int zero_heuristic(int a, int b) {
    return 0;
}

void search(const graph_data& graph, int start, int end, std::vector<bool>& visited, 
           std::vector<int>& g, std::vector<int>& parent, PriorityQueue* queue, 
           std::atomic<int>& meeting_node, std::vector<int>& explored_nodes, 
           const std::vector<bool>& opposite_visited) {
    
    while (!queue->empty() && !found.load(std::memory_order_relaxed)) {
        Node node = queue->top();
        queue->pop();

        if (visited[node.vertex]) continue;
        
        visited[node.vertex] = true;
        explored_nodes.push_back(node.vertex);

        if (opposite_visited[node.vertex]) {
            found.store(true, std::memory_order_relaxed);
            meeting_node.store(node.vertex);
            return;
        }

        for (const auto& [next, weight] : graph.adjacency[node.vertex]) {
            if (!visited[next]) {
                int new_g = g[node.vertex] + weight;
                if (new_g < g[next]) {
                    g[next] = new_g;
                    parent[next] = node.vertex;
                    queue->push(Node(new_g + zero_heuristic(next, end), new_g, next));
                }
            }
        }
    }
}

std::optional<std::vector<int>> bidirectional_astar(const graph_data& graph, int start, int end, std::vector<int>& distances) {
    // Reset the found flag at the start of each call
    found.store(false, std::memory_order_relaxed);

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

    found.store(false, std::memory_order_relaxed);

    auto future_forward = std::async(std::launch::async, [&]() {
        search(graph, start, end, visited_forward, g_forward, parent_forward, 
               &forward_queue, meeting_node, explored_forward, visited_backward);
    });

    auto future_backward = std::async(std::launch::async, [&]() {
        search(graph, end, start, visited_backward, g_backward, parent_backward, 
               &backward_queue, meeting_node, explored_backward, visited_forward);
    });

    future_forward.get();
    future_backward.get();

    if (meeting_node.load() == -1) return std::nullopt;

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
