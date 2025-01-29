#include "graph_data.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

using namespace std;

struct are_extremities_singles
{
	bool is_start_single = false;
	bool is_end_single = false;
};

void preprocess(graph_data *graph, unordered_map<int, int> *single_neighbors)
{

	// Iterate through the adjacency list
	for (auto &[node, neighbors] : graph->adjacency)
	{
		// If the node has only 1 neighbor
		if (neighbors.size() == 1)
		{
			// Store the neighbor in the single_neighbors map
			single_neighbors->operator[](node) = neighbors[0].first;

			// Remove the node from the adjacency list
			graph->adjacency.erase(node);
		}
	}

	// Iterate through the single_neighbors map to print it
	cout << "Single neighbors count:\n";
	cout << single_neighbors->size() << endl;
}

void preprocessDoubleNeighbors(graph_data *graph, unordered_map<int, int> *double_neighbors)
{

	// Iterate through the adjacency list
	for (auto &[node, neighbors] : graph->adjacency)
	{
		// If the node has only 2 neighbors
		if (neighbors.size() == 2)
		{
			// Store the neighbor in the double_neighbors map
			double_neighbors->operator[](node) = neighbors[0].first;

		}
	}

	// Iterate through the single_neighbors map to print it
	cout << "Double neighbors count:\n";
	cout << double_neighbors->size() << endl;
}

void check_single_start_or_end(int *start, int *end, unordered_map<int, int> *single_neighbors, are_extremities_singles *yes)
{
	// Check if the start node is a single neighbor
	if (single_neighbors->find(*start) != single_neighbors->end())
	{
		cout << "Start node is a single neighbor: " << start << " -> " << single_neighbors->at(*start) << endl;
		*start = single_neighbors->at(*start);
		yes->is_start_single = true;
	}

	// Check if the end node is a single neighbor
	if (single_neighbors->find(*end) != single_neighbors->end())
	{
		cout << "End node is a single neighbor: " << end << " -> " << single_neighbors->at(*end) << endl;
		*end = single_neighbors->at(*end);
		yes->is_end_single = true;
	}
}