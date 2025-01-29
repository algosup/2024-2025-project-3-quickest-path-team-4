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
	string file_path = "USAroads.csv";

	// Load the graph data
	graph_data gdata = load_graph_data(file_path);

	unordered_map<int, int> single_neighbors;

	preprocess(&gdata, &single_neighbors);

	// Define the start and end nodes
	int start;
	int end;
	
	cout << "ready" << endl;

	cout << "Start node: ";
	cin >> start;
	cout << "End node: ";
	cin >> end;

	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	cout << "Processing." << endl;

	// Find the shortest path using Dijkstra's algorithm
	auto result = dijkstra(gdata, start, end);

	chrono::steady_clock::time_point stop = chrono::steady_clock::now();

	if (result.has_value())
	{
		cout << "Shortest path from " << start << " to " << end << ": ";
		for (int i = 0; i < result.value().size(); i++)
		{
			cout << result.value()[i] << " ";
			if (result.value()[i] == end)
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