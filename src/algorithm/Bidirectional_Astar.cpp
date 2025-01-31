#include "graph_data.h"
#include <queue>
#include <thread>
#include <mutex>
#include <vector>
#include <limits>
#include <algorithm>
#include <optional>

using namespace std;

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

using Heap = priority_queue<Node, vector<Node>, NodeComparator>;

// Improved heuristic using landmark distances and minimum edge weight
inline int improved_heuristic(int a, int b, const graph_data& graph, const vector<vector<int>>& landmark_distances) {
    int min_dist = numeric_limits<int>::max();
    for (const auto& distances : landmark_distances) {
        int dist = abs(distances[a] - distances[b]);
        if (dist < min_dist) {
            min_dist = dist;
        }
    }
    return min_dist * graph.min_edge_weight;
}

// Mutex for thread-safe access to shared data
mutex mtx;

// Forward search function
void forward_search(const graph_data& graph, int start, int end, vector<bool>& visited, vector<int>& g, vector<int>& parent, Heap& queue, const vector<vector<int>>& landmark_distances) {
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
                int f = new_g + improved_heuristic(next, end, graph, landmark_distances);
                mtx.lock();
                queue.push(Node(f, new_g, next));
                mtx.unlock();
            }
        }
    }
}

// Backward search function
void backward_search(const graph_data& graph, int start, int end, vector<bool>& visited, vector<int>& g, vector<int>& parent, Heap& queue, const vector<vector<int>>& landmark_distances) {
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
                int f = new_g + improved_heuristic(next, start, graph, landmark_distances);
                mtx.lock();
                queue.push(Node(f, new_g, next));
                mtx.unlock();
            }
        }
    }
}

optional<vector<int>> bidirectional_astar(const graph_data& graph, int start, int end, vector<int>& distances, const vector<vector<int>>& landmark_distances) {
    if (start == end) {
        distances[start] = 0;
        return vector<int>{start};
    }

    const size_t n = graph.adjacency.size();

    // Pre-allocate all vectors to avoid resizing
    vector<bool> visited_forward(n), visited_backward(n);
    vector<int> g_forward(n, numeric_limits<int>::max());
    vector<int> g_backward(n, numeric_limits<int>::max());
    vector<int> parent_forward(n, -1);
    vector<int> parent_backward(n, -1);

    g_forward[start] = 0;
    g_backward[end] = 0;

    // Use priority queues with the custom comparator
    Heap forward_queue, backward_queue;
    forward_queue.push(Node(improved_heuristic(start, end, graph, landmark_distances), 0, start));
    backward_queue.push(Node(improved_heuristic(end, start, graph, landmark_distances), 0, end));

    // Run forward and backward searches in parallel
    thread forward_thread(forward_search, ref(graph), start, end, ref(visited_forward), ref(g_forward), ref(parent_forward), ref(forward_queue), ref(landmark_distances));
    thread backward_thread(backward_search, ref(graph), start, end, ref(visited_backward), ref(g_backward), ref(parent_backward), ref(backward_queue), ref(landmark_distances));

    forward_thread.join();
    backward_thread.join();

    // Find the meeting node
    int best_path = numeric_limits<int>::max();
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

    if (meeting_node == -1) return nullopt;

    // Reconstruct path
    vector<int> path;
    for (int at = meeting_node; at != -1; at = parent_forward[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

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