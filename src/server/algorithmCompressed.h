#ifndef BIDIRECTIONAL_ASTAR_H
#define BIDIRECTIONAL_ASTAR_H

#include "graphDataCompressed.h"
#include <optional>
#include <vector>

std::optional<std::vector<int>> bidirectional_astar(const graph_data& graph, int start, int end, std::vector<int>& distances, const std::vector<std::vector<int>>& landmark_distances);

#endif // BIDIRECTIONAL_ASTAR_H