#include <queue>
#include <unordered_map>
#include <vector>
#include <limits>
#include <iostream>
#include <optional>
#include <algorithm>

using namespace std;

#include "graph_data.h"

// Dijkstra's algorithm
optional<vector<int>> dijkstra(const graph_data &g_data, int start, int end, unordered_map<int, int> *distances)
{
	// Priority queue to store (distance, node), with the smallest distance at the top
	using NodeDist = pair<int, int>;
	priority_queue<NodeDist, vector<NodeDist>, greater<>> pq;


	// Predecessor map: used to reconstruct the shortest path
	unordered_map<int, int> predecessors;

	// Add the start node to the priority queue
	pq.emplace(0, start);

	// Main loop
	while (!pq.empty())
	{
		auto [current_dist, current_node] = pq.top();
		pq.pop();

		// If we've reached the destination node, stop
		if (current_node == end)
		{
			break;
		}

		// Traverse neighbors of the current node
		for (const auto &[neighbor, weight] : g_data.adjacency.at(current_node))
		{
			int new_dist = current_dist + weight;

			// If a shorter path to the neighbor is found
			if (new_dist < (*distances)[neighbor])
			{
				(*distances)[neighbor] = new_dist;
				predecessors[neighbor] = current_node;
				pq.emplace(new_dist, neighbor);
			}
		}
	}

	// If the end node is unreachable
	if ((*distances)[end] == numeric_limits<int>::max())
	{
		return nullopt;
	}

	// Reconstruct the path from end to start using the predecessors map
	vector<int> path;
	for (int at = end; at != start; at = predecessors[at])
	{
		path.push_back(at);
	}
	path.push_back(start);

	// Reverse the path to go from start to end
	reverse(path.begin(), path.end());
	return path;
}
