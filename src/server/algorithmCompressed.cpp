#include "algorithmCompressed.h"
#include <iostream>  // Add this line
#include <algorithm>
#include <thread>
#include <mutex>

std::optional<std::vector<int>> bidirectional_astar(const graph_data& graph, int start, int end, std::vector<int>& distances, const std::vector<std::vector<int>>& landmark_distances) {
    std::cout << "Running bidirectional A*..." << std::endl;
    return std::nullopt;
}