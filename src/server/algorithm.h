#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "graphData.h"
#include <vector>
#include <optional>

// Function declaration for biDirectionalDijkstra
std::optional<std::vector<int>> biDirectionalDijkstra(const GraphData& g_data, int start, int end, std::vector<int>& distances);

#endif // ALGORITHM_H