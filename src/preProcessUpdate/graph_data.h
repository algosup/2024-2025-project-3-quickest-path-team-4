#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

struct graph_data
{
	// Maps each node to a unique index
	unordered_map<int, size_t> node_to_index;

	// Adjacency list: maps each node to its neighbors and the cost of edges
	unordered_map<int, vector<pair<int, int>>> adjacency;

	// Prints the contents of the graph_data
	void print_contents() const
	{
		cout << "Graph Data:\n";

		cout << "Nodes and their indices:\n";
		for (const auto &[node, index] : node_to_index)
		{
			cout << "Node: " << node << ", Index: " << index << "\n";
		}

		cout << "\nAdjacency List:\n";
		for (const auto &[node, neighbors] : adjacency)
		{
			cout << "Node " << node << " -> ";
			for (const auto &[neighbor, cost] : neighbors)
			{
				cout << "(" << neighbor << ", " << cost << ") ";
			}
			cout << "\n";
		}
	}
};
