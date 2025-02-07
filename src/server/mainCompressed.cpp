#include <iostream>
#include <unordered_map>
#include <vector>
#include "loadingCompressed.h"
#include "preprocessCompressed.h"
#include "algorithmCompressed.h"
#include "saveLoadBinaryCompressed.h"  // Include the new header file

using namespace std;

int main() {
    string file_path = "USA-roads.csv";
    string compressed_paths_file = "compressed_paths.bin";

    // Load the graph data
    graph_data g_data = load_graph_data(file_path);

    // Preprocess the graph
    unordered_map<int, int> single_neighbors;
    preprocess(&g_data, &single_neighbors);

    // Example compressed paths data
    unordered_map<int, unordered_map<int, path_info>> compressed_paths;
    compressed_paths[1][3] = {{2}, 10};  // Path from 1 to 3 with intermediate node 2 and total distance 10
    compressed_paths[5][7] = {{6}, 15};  // Path from 5 to 7 with intermediate node 6 and total distance 15

    // Save compressed paths to binary file
    save_compressed_paths_binary(compressed_paths_file, compressed_paths);

    // Load compressed paths from binary file
    unordered_map<int, unordered_map<int, path_info>> loaded_compressed_paths;
    if (load_compressed_paths_binary(compressed_paths_file, loaded_compressed_paths)) {
        cout << "Successfully loaded compressed paths from binary file." << endl;

        // Print loaded compressed paths
        for (const auto& [start, end_map] : loaded_compressed_paths) {
            for (const auto& [end, info] : end_map) {
                cout << "Path from " << start << " to " << end << ": ";
                cout << "Distance = " << info.total_distance << ", Intermediate nodes = ";
                for (int node : info.intermediate_nodes) {
                    cout << node << " ";
                }
                cout << endl;
            }
        }
    } else {
        cerr << "Failed to load compressed paths from binary file." << endl;
    }

    return 0;
}

// g++ -std=c++17 -o save_load_binary save_load_binary_compressed.cpp main_compressed.cpp loading_compressed.cpp preprocess_compressed.cpp Bidirectional_Astar_compressed.cpp