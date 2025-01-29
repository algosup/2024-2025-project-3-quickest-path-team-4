#include <queue>
#include <unordered_map>
#include <vector>
#include <limits>
#include <iostream>
#include <optional>
#include <algorithm>

using namespace std;

#include "graph_data.h"

// Custom comparator for the priority queue
struct CompareNodeDist {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.first > b.first;
    }
};

// Helper function to process one step of either forward or backward search
static bool process_step(const graph_data& g_data,
                       priority_queue<pair<int, int>, vector<pair<int, int>>, CompareNodeDist>& pq,
                       vector<int>& dist_current,
                       const vector<int>& dist_opposite,
                       vector<int>& pred,
                       vector<bool>& visited,
                       int& best_meeting_dist,
                       int& meeting_node,
                       bool is_backward) {
    const auto [current_dist, current_node] = pq.top();
    pq.pop();

    if (visited[current_node]) {
        return false;
    }
    visited[current_node] = true;

    // Check for intersection
    if (dist_opposite[current_node] != numeric_limits<int>::max()) {
        int total_dist = current_dist + dist_opposite[current_node];
        if (total_dist < best_meeting_dist) {
            best_meeting_dist = total_dist;
            meeting_node = current_node;
        }
        return true;
    }

    auto it = g_data.adjacency.find(current_node);
    if (it == g_data.adjacency.end()) {
        return false;
    }

    for (const auto& [neighbor, weight] : it->second) {
        if (visited[neighbor]) continue;
        
        int new_dist = current_dist + weight;
        if (new_dist < dist_current[neighbor]) {
            dist_current[neighbor] = new_dist;
            pred[neighbor] = current_node;
            pq.emplace(new_dist, neighbor);
        }
    }

    return false;
}

optional<vector<int>> bidirectional_dijkstra(const graph_data& g_data, int start, int end, unordered_map<int, int>* distances) {
    if (start == end) {
        (*distances)[start] = 0;
        return vector<int>{start};
    }

    // Use vector<bool> for visited nodes (more efficient than unordered_map)
    const int max_node = [&g_data]() {
        int max_id = 0;
        for (const auto& [node, _] : g_data.adjacency) {
            max_id = max(max_id, node);
        }
        return max_id + 1;
    }();

    vector<bool> visited_forward(max_node), visited_backward(max_node);
    vector<int> dist_forward(max_node, numeric_limits<int>::max());
    vector<int> dist_backward(max_node, numeric_limits<int>::max());
    vector<int> pred_forward(max_node, -1);
    vector<int> pred_backward(max_node, -1);

    // Initialize distances for start and end
    dist_forward[start] = 0;
    dist_backward[end] = 0;

    // Use custom comparator for better performance
    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareNodeDist> pq_forward, pq_backward;
    pq_forward.emplace(0, start);
    pq_backward.emplace(0, end);

    int best_meeting_dist = numeric_limits<int>::max();
    int meeting_node = -1;

    // Main loop with early termination condition
    while (!pq_forward.empty() && !pq_backward.empty()) {
        // Early termination check
        const int min_forward = pq_forward.top().first;
        const int min_backward = pq_backward.top().first;
        if (min_forward + min_backward >= best_meeting_dist) {
            break;
        }

        // Forward search
        if (process_step(g_data, pq_forward, dist_forward, dist_backward, 
                        pred_forward, visited_forward, best_meeting_dist, 
                        meeting_node, false)) {
            break;
        }

        // Backward search
        if (process_step(g_data, pq_backward, dist_backward, dist_forward, 
                        pred_backward, visited_backward, best_meeting_dist, 
                        meeting_node, true)) {
            break;
        }
    }

    if (meeting_node == -1) {
        return nullopt;
    }

    // Reconstruct path efficiently
    vector<int> path;
    path.reserve(max_node); // Pre-allocate memory

    // Forward path
    for (int at = meeting_node; at != -1; at = pred_forward[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    // Backward path
    for (int at = pred_backward[meeting_node]; at != -1; at = pred_backward[at]) {
        path.push_back(at);
    }

    // Update distances map efficiently
    for (int i = 0; i < max_node; ++i) {
        if (dist_forward[i] != numeric_limits<int>::max()) {
            (*distances)[i] = dist_forward[i];
        }
        if (dist_backward[i] != numeric_limits<int>::max()) {
            (*distances)[i] = min((*distances)[i], dist_backward[i]);
        }
    }

    return path;
}