#include "Bidirectional_Astar.h"
#include <thread>
#include <future>
#include <algorithm>

// Define the mutex here
std::mutex mtx;

// Improved heuristic using Euclidean distance (assuming coordinates are available)
inline int euclidean_heuristic(int a, int b, const graph_data& graph) {
    // Assuming graph has coordinates for each node
    int dx = graph.coordinates[a].x - graph.coordinates[b].x;
    int dy = graph.coordinates[a].y - graph.coordinates[b].y;
    return static_cast<int>(std::sqrt(dx * dx + dy * dy));
}

// Forward search function
void forward_search(const graph_data& graph, int start, int end, std::vector<bool>& visited, std::vector<int>& g, std::vector<int>& parent, Heap& queue, const std::vector<std::vector<int>>& landmark_distances) {
    while (true) {
        mtx.lock();
        if (queue.empty()) {
            mtx.unlock();
            break;
        }
        auto node = queue.top();
        queue.pop();
        mtx.unlock();

        int curr = node.vertex;
        if (visited[curr]) continue;
        visited[curr] = true;

        for (const auto& [next, weight] : graph.adjacency[curr]) {
            if (visited[next]) continue;

            int new_g = node.g + weight;
            if (new_g < g[next]) {
                g[next] = new_g;
                parent[next] = curr;
                int f = new_g + euclidean_heuristic(next, end, graph);
                mtx.lock();
                queue.push(Node(f, new_g, next));
                mtx.unlock();
            }
        }
    }
}

// Backward search function
void backward_search(const graph_data& graph, int start, int end, std::vector<bool>& visited, std::vector<int>& g, std::vector<int>& parent, Heap& queue, const std::vector<std::vector<int>>& landmark_distances) {
    while (true) {
        mtx.lock();
        if (queue.empty()) {
            mtx.unlock();
            break;
        }
        auto node = queue.top();
        queue.pop();
        mtx.unlock();

        int curr = node.vertex;
        if (visited[curr]) continue;
        visited[curr] = true;

        for (const auto& [next, weight] : graph.adjacency[curr]) {
            if (visited[next]) continue;

            int new_g = node.g + weight;
            if (new_g < g[next]) {
                g[next] = new_g;
                parent[next] = curr;
                int f = new_g + euclidean_heuristic(next, start, graph);
                mtx.lock();
                queue.push(Node(f, new_g, next));
                mtx.unlock();
            }
        }
    }
}

std::optional<std::vector<int>> bidirectional_astar(const graph_data& graph, int start, int end, std::vector<int>& distances, const std::vector<std::vector<int>>& landmark_distances) {
    if (start == end) {
        distances[start] = 0;
        return std::vector<int>{start};
    }

    const size_t n = graph.adjacency.size();

    // Pre-allocate all vectors to avoid resizing
    std::vector<bool> visited_forward(n), visited_backward(n);
    std::vector<int> g_forward(n, std::numeric_limits<int>::max());
    std::vector<int> g_backward(n, std::numeric_limits<int>::max());
    std::vector<int> parent_forward(n, -1);
    std::vector<int> parent_backward(n, -1);

    g_forward[start] = 0;
    g_backward[end] = 0;

    // Use priority queues with the custom comparator
    Heap forward_queue, backward_queue;
    forward_queue.push(Node(euclidean_heuristic(start, end, graph), 0, start));
    backward_queue.push(Node(euclidean_heuristic(end, start, graph), 0, end));

    // Run forward and backward searches in parallel using std::async
    auto future_forward = std::async(std::launch::async, forward_search, std::ref(graph), start, end, std::ref(visited_forward), std::ref(g_forward), std::ref(parent_forward), std::ref(forward_queue), std::ref(landmark_distances));
    auto future_backward = std::async(std::launch::async, backward_search, std::ref(graph), start, end, std::ref(visited_backward), std::ref(g_backward), std::ref(parent_backward), std::ref(backward_queue), std::ref(landmark_distances));

    future_forward.get();
    future_backward.get();

    // Find the meeting node
    int best_path = std::numeric_limits<int>::max();
    int meeting_node = -1;
    for (size_t i = 0; i < n; ++i) {
        if (visited_forward[i] && visited_backward[i]) {
            int total_dist = g_forward[i] + g_backward[i];
            if (total_dist < best_path) {
                best_path = total_dist;
                meeting_node = i;
            }
        }
    }

    if (meeting_node == -1) return std::nullopt;

    // Reconstruct path
    std::vector<int> path;
    for (int at = meeting_node; at != -1; at = parent_forward[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    for (int at = parent_backward[meeting_node]; at != -1; at = parent_backward[at]) {
        path.push_back(at);
    }

    // Update distances
    distances = std::move(g_forward);
    for (size_t i = 0; i < n; ++i) {
        if (g_backward[i] < distances[i]) {
            distances[i] = g_backward[i];
        }
    }

    return path;
}