#include "Bidirectional_Astar.h"
#include <thread>
#include <future>
#include <algorithm>
#include <atomic>

std::mutex forward_mtx, backward_mtx;
std::atomic<bool> found(false);

inline int zero_heuristic(int a, int b) {
    return 0;
}

void forward_search(const graph_data& graph, int start, int end, std::vector<bool>& visited, std::vector<int>& g, std::vector<int>& parent, Heap& queue) {
    while (!found) {
        forward_mtx.lock();
        if (queue.empty()) {
            forward_mtx.unlock();
            break;
        }
        std::pop_heap(queue.begin(), queue.end(), cmp);
        auto node = queue.back();
        queue.pop_back();
        forward_mtx.unlock();

        int curr = node.vertex;
        if (visited[curr]) continue;
        visited[curr] = true;

        for (const auto& [next, weight] : graph.adjacency[curr]) {
            if (visited[next]) continue;

            int new_g = node.g + weight;
            if (new_g < g[next]) {
                g[next] = new_g;
                parent[next] = curr;
                int f = new_g + zero_heuristic(next, end);
                forward_mtx.lock();
                queue.push_back(Node(f, new_g, next));
                std::push_heap(queue.begin(), queue.end(), cmp);
                forward_mtx.unlock();
            }
        }
    }
}

void backward_search(const graph_data& graph, int start, int end, std::vector<bool>& visited, std::vector<int>& g, std::vector<int>& parent, Heap& queue) {
    while (!found) {
        backward_mtx.lock();
        if (queue.empty()) {
            backward_mtx.unlock();
            break;
        }
        std::pop_heap(queue.begin(), queue.end(), cmp);
        auto node = queue.back();
        queue.pop_back();
        backward_mtx.unlock();

        int curr = node.vertex;
        if (visited[curr]) continue;
        visited[curr] = true;

        for (const auto& [next, weight] : graph.adjacency[curr]) {
            if (visited[next]) continue;

            int new_g = node.g + weight;
            if (new_g < g[next]) {
                g[next] = new_g;
                parent[next] = curr;
                int f = new_g + zero_heuristic(next, start);
                backward_mtx.lock();
                queue.push_back(Node(f, new_g, next));
                std::push_heap(queue.begin(), queue.end(), cmp);
                backward_mtx.unlock();
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

    std::vector<bool> visited_forward(n), visited_backward(n);
    std::vector<int> g_forward(n, std::numeric_limits<int>::max());
    std::vector<int> g_backward(n, std::numeric_limits<int>::max());
    std::vector<int> parent_forward(n, -1);
    std::vector<int> parent_backward(n, -1);

    g_forward[start] = 0;
    g_backward[end] = 0;

    Heap forward_queue, backward_queue;
    forward_queue.push_back(Node(zero_heuristic(start, end), 0, start));
    std::push_heap(forward_queue.begin(), forward_queue.end(), cmp);
    backward_queue.push_back(Node(zero_heuristic(end, start), 0, end));
    std::push_heap(backward_queue.begin(), backward_queue.end(), cmp);

    auto future_forward = std::async(std::launch::async, forward_search, std::ref(graph), start, end, std::ref(visited_forward), std::ref(g_forward), std::ref(parent_forward), std::ref(forward_queue));
    auto future_backward = std::async(std::launch::async, backward_search, std::ref(graph), start, end, std::ref(visited_backward), std::ref(g_backward), std::ref(parent_backward), std::ref(backward_queue));

    future_forward.get();
    future_backward.get();

    int best_path = std::numeric_limits<int>::max();
    int meeting_node = -1;
    for (size_t i = 0; i < n; ++i) {
        if (visited_forward[i] && visited_backward[i]) {
            int total_dist = g_forward[i] + g_backward[i];
            if (total_dist < best_path) {
                best_path = total_dist;
                meeting_node = i;
                found = true;
            }
        }
    }

    if (meeting_node == -1) return std::nullopt;

    std::vector<int> path;
    for (int at = meeting_node; at != -1; at = parent_forward[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    for (int at = parent_backward[meeting_node]; at != -1; at = parent_backward[at]) {
        path.push_back(at);
    }

    distances = std::move(g_forward);
    for (size_t i = 0; i < n; ++i) {
        if (g_backward[i] < distances[i]) {
            distances[i] = g_backward[i];
        }
    }

    return path;
}