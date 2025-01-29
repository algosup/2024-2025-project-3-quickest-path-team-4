#include <iostream>
#include <string>
#include <chrono>
#include "graph_data.h"
#include "loading.cpp"
#include "Dijkstra.cpp"
#include "preprocess.cpp"

using namespace std;

int main()
{
	// Path to the input file
	string file_path = "USA-roads.csv";

	are_extremities_singles are_they;

	// Load the graph data
	graph_data g_data = load_graph_data(file_path);

	// Create a new adjacency list to store the nodes that only contains 1 neighbor
	unordered_map<int, int> single_neighbors;

	// Create a new adjacency list to store the nodes that only contains 2 neighbors
	unordered_map<int, int> double_neighbors;


	preprocess(&g_data, &single_neighbors);

	preprocessDoubleNeighbors(&g_data, &double_neighbors);

	// Define the start and end nodes
	int start;
	int end;

	// Distance map: node -> shortest distance from the start node
	unordered_map<int, int> distances;
	
	// Initialize distances to infinity and start node to 0
	for (const auto &[node, _] : g_data.adjacency)
	{
		distances[node] = numeric_limits<int>::max();
	}

	cout << "ready" << endl;

	cout << "Start node: ";
	cin >> start;
	cout << "End node: ";
	cin >> end;
	int true_start = start;
	int true_end = end;

	distances[start] = 0;

	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	check_single_start_or_end(&start, &end, &single_neighbors, &are_they);
	cout << "Processing." << endl;

	// Find the shortest path using Dijkstra's algorithm
	auto result = dijkstra(g_data, start, end, &distances);

	chrono::steady_clock::time_point stop = chrono::steady_clock::now();

	if (result.has_value())
	{
		if (are_they.is_start_single)
		{
			result.value().insert(result.value().begin(), start);
		}
		if (are_they.is_end_single)
		{
			result.value().push_back(end);
		}
		cout << "Shortest path from " << true_start << " to " << true_end << ": ";
		for (int i = 0; i < result.value().size(); i++)
		{
			cout << result.value()[i] << " ";
			if (result.value()[i] == true_end)
			{
				cout << endl;
				break;
			}
		}
	}
	else
	{
		cout << "No path found from " << start << " to " << end << endl;
	}
	cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds>(stop - begin).count() << "[ms]" << endl;
	cout << "Nodes: " << result.value().size() << endl;

	return 0;
}
