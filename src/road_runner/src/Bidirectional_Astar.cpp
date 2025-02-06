#include <queue>
#include <vector>
#include <cstdint>
#include <algorithm>
#include "Bidirectional_Astar.h"
#include <thread>
#include <future>
#include <queue>
#include <atomic>
#include <iostream>

// Cache-aligned node structure
struct alignas(32) FastNode {
    int32_t vertex;
    int32_t parent;
    int32_t g;
    float f;
    static constexpr size_t INITIAL_SIZE = 1024;
};
// Custom binary heap for better cache locality
class BinaryHeap {
private:
    alignas(64) std::vector<FastNode> data;
    static constexpr size_t HEAP_INITIAL_SIZE = FastNode::INITIAL_SIZE;

    __attribute__((always_inline)) void siftUp(size_t idx) {
        FastNode temp = data[idx];
        while (idx > 0) {
            size_t parent = (idx - 1) >> 1;
            if (data[parent].f <= temp.f) break;
            data[idx] = data[parent];
            idx = parent;
        }
        data[idx] = temp;
    }
    
    __attribute__((always_inline)) void siftDown(size_t idx) {
        FastNode temp = data[idx];
        size_t size = data.size();
        while (true) {
            size_t smallest = idx;
            size_t left = (idx << 1) + 1;
            size_t right = left + 1;
            
            if (left < size && data[left].f < temp.f) smallest = left;
            if (right < size && data[right].f < (smallest == idx ? temp.f : data[left].f)) smallest = right;
            if (smallest == idx) break;
            data[idx] = data[smallest];
            idx = smallest;
        }
        data[idx] = temp;
    }

public:
    BinaryHeap() { data.reserve(HEAP_INITIAL_SIZE); }
    bool empty() const { return data.empty(); }
    void clear() { data.clear(); }
    
    __attribute__((always_inline)) void push(const FastNode& node) {
        data.push_back(node);
        siftUp(data.size() - 1);
    }
    
    __attribute__((always_inline)) FastNode pop() {
        FastNode top = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) siftDown(0);
        return top;
    }
};

std::optional<std::vector<int>> bidirectional_astar(const GraphData& graph, int start, int end, std::vector<int>& distances) {
    const size_t n = graph.size(); // Use size() instead of get_node_count()
    // ...existing code...
    if (start == end) {
        distances[start] = 0;
        return std::vector<int>{start};
    }

    static BinaryHeap forward_queue, backward_queue;
    static std::vector<uint8_t> visited_forward(n), visited_backward(n);
    static std::vector<int32_t> g_forward(n), g_backward(n);
    static std::vector<int32_t> parent_forward(n), parent_backward(n);

    std::fill(visited_forward.begin(), visited_forward.end(), 0);
    std::fill(visited_backward.begin(), visited_backward.end(), 0);
    std::fill(g_forward.begin(), g_forward.end(), INT32_MAX);
    std::fill(g_backward.begin(), g_backward.end(), INT32_MAX);
    std::fill(parent_forward.begin(), parent_forward.end(), -1);
    std::fill(parent_backward.begin(), parent_backward.end(), -1);

    forward_queue.clear();
    backward_queue.clear();

    g_forward[start] = 0;
    g_backward[end] = 0;

    forward_queue.push({start, -1, 0, 0.0f});
    backward_queue.push({end, -1, 0, 0.0f});

    int32_t meeting_node = -1;
    int32_t best_path_length = INT32_MAX;
    const int32_t MAX_DISTANCE = INT32_MAX >> 1;

    while (!forward_queue.empty() && !backward_queue.empty()) {
        // Forward search
        auto curr_f = forward_queue.pop();
        if (visited_forward[curr_f.vertex] || curr_f.g >= best_path_length) continue;
        
        visited_forward[curr_f.vertex] = 1;

        if (visited_backward[curr_f.vertex]) {
            int32_t path_length = curr_f.g + g_backward[curr_f.vertex];
            if (path_length < best_path_length) {
                best_path_length = path_length;
                meeting_node = curr_f.vertex;
            }
            continue;
        }

        const auto& neighbors = graph.get_neighbors(curr_f.vertex);
        for (const auto& [next, weight] : neighbors) {
            if (visited_forward[next] || curr_f.g + weight >= MAX_DISTANCE) continue;
            
            int32_t new_g = curr_f.g + weight;
            if (new_g < g_forward[next]) {
                g_forward[next] = new_g;
                parent_forward[next] = curr_f.vertex;
                forward_queue.push({next, curr_f.vertex, new_g, static_cast<float>(new_g)});
            }
        }

        // Backward search
        auto curr_b = backward_queue.pop();
        if (visited_backward[curr_b.vertex] || curr_b.g >= best_path_length) continue;
        
        visited_backward[curr_b.vertex] = 1;

        if (visited_forward[curr_b.vertex]) {
            int32_t path_length = curr_b.g + g_forward[curr_b.vertex];
            if (path_length < best_path_length) {
                best_path_length = path_length;
                meeting_node = curr_b.vertex;
            }
            continue;
        }

        const auto& back_neighbors = graph.get_neighbors(curr_b.vertex);
        for (const auto& [next, weight] : back_neighbors) {
            if (visited_backward[next] || curr_b.g + weight >= MAX_DISTANCE) continue;
            
            int32_t new_g = curr_b.g + weight;
            if (new_g < g_backward[next]) {
                g_backward[next] = new_g;
                parent_backward[next] = curr_b.vertex;
                backward_queue.push({next, curr_b.vertex, new_g, static_cast<float>(new_g)});
            }
        }
    }

    if (meeting_node == -1) return std::nullopt;

    std::vector<int> path;
    path.reserve(64);
    
    for (int32_t at = meeting_node; at != -1; at = parent_forward[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    
    for (int32_t at = parent_backward[meeting_node]; at != -1; at = parent_backward[at]) {
        path.push_back(at);
    }

    distances = std::move(g_forward);
    return path;
}

// 9489093 → 22377087 : 13323 Nodes