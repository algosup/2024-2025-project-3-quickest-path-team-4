#include "graph_data.h" // Include the graph_data header
#include <queue>
#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>
#include <optional>

using namespace std;

// Simplified node representation for the priority queue
struct Node
{
    int f;
    int g;
    int vertex;

    Node(int f_, int g_, int v_) : f(f_), g(g_), vertex(v_) {}

    bool operator>(const Node &other) const
    {
        return f > other.f;
    }
};

// Manhattan distance heuristic But nothing
inline int heuristic(int a, int b)
{
    return 0;
}

optional<vector<int>> bidirectional_astar(const graph_data& graph, int start, int end, unordered_map<int, int>& distances) {
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

    // Use priority queues with the simplified Node struct
    priority_queue<Node, vector<Node>, greater<>> forward_queue, backward_queue;
    forward_queue.emplace(heuristic(start, end), 0, start);
    backward_queue.emplace(heuristic(end, start), 0, end);

    int best_path = numeric_limits<int>::max();
    int meeting_node = -1;

    // Main search loop
    while (!forward_queue.empty() && !backward_queue.empty()) {
        // Early termination check
        if (forward_queue.top().f + backward_queue.top().f >= best_path) break;

        // Forward search
        auto [f_curr, g_curr, curr] = forward_queue.top();
        forward_queue.pop();

        if (visited_forward[curr]) continue;
        visited_forward[curr] = true;

        // Check for intersection
        if (visited_backward[curr]) {
            int total_dist = g_curr + g_backward[curr];
            if (total_dist < best_path) {
                best_path = total_dist;
                meeting_node = curr;
            }
            continue;
        }

        // Process neighbors
        for (const auto& [next, weight] : graph.adjacency.at(curr)) {
            if (visited_forward[next]) continue;

            int new_g = g_curr + weight;
            if (new_g < g_forward[next]) {
                g_forward[next] = new_g;
                parent_forward[next] = curr;
                int f = new_g + heuristic(next, end);
                forward_queue.emplace(f, new_g, next);
            }
        }

        // Backward search (similar to forward search)
        auto [b_f_curr, b_g_curr, b_curr] = backward_queue.top();
        backward_queue.pop();

        if (visited_backward[b_curr]) continue;
        visited_backward[b_curr] = true;

        if (visited_forward[b_curr]) {
            int total_dist = b_g_curr + g_forward[b_curr];
            if (total_dist < best_path) {
                best_path = total_dist;
                meeting_node = b_curr;
            }
            continue;
        }

        for (const auto& [next, weight] : graph.adjacency.at(b_curr)) {
            if (visited_backward[next]) continue;

            int new_g = b_g_curr + weight;
            if (new_g < g_backward[next]) {
                g_backward[next] = new_g;
                parent_backward[next] = b_curr;
                int f = new_g + heuristic(next, start);
                backward_queue.emplace(f, new_g, next);
            }
        }
    }

    if (meeting_node == -1) return nullopt;

    // Reconstruct path
    vector<int> path;
    path.reserve(n);

    for (int at = meeting_node; at != -1; at = parent_forward[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    for (int at = parent_backward[meeting_node]; at != -1; at = parent_backward[at]) {
        path.push_back(at);
    }

    // Update distances
    for (size_t i = 0; i < n; ++i) {
        if (g_backward[i] < distances[i]) {
            distances[i] = g_backward[i];
        }
    }

    return path;
}