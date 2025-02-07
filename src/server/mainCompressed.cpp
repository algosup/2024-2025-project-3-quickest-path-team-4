#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include "loadingCompressed.h"
#include "preprocessCompressed.h"
#include "algorithmCompressed.h"
#include "saveLoadBinaryCompressed.h"

using namespace std;
using namespace std::chrono;

int main() {
    string file_path = "USA-roads.csv";
    string binary_cache_file = "path_cache.bin";

    cout << "Loading graph data from CSV..." << endl;
    auto start = high_resolution_clock::now();
    
    // Load the graph data
    graph_data g_data = load_graph_data(file_path);
    
    auto csv_load_time = duration_cast<milliseconds>(high_resolution_clock::now() - start);
    cout << "CSV loading time: " << csv_load_time.count() << "ms" << endl;

    // Initialize compressed paths storage
    unordered_map<int, unordered_map<int, path_info>> compressed_paths;
    
    cout << "Preprocessing graph and generating path cache..." << endl;
    start = high_resolution_clock::now();

    // Preprocess graph and generate frequently used paths
    unordered_map<int, int> single_neighbors;
    preprocess(&g_data, &single_neighbors);

    // Generate path cache for frequently accessed nodes
    const int cache_limit = 1000; // Adjust based on memory constraints
    int nodes_processed = 0;

    for (size_t i = 0; i < g_data.adjacency.size() && nodes_processed < cache_limit; ++i) {
        if (g_data.adjacency[i].size() > 2) { // Focus on important nodes
            vector<int> distances(g_data.adjacency.size(), numeric_limits<int>::max());
            auto result = bidirectional_astar(g_data, i, -1, distances); // -1 means compute all paths
            
            for (size_t j = 0; j < distances.size(); ++j) {
                if (distances[j] != numeric_limits<int>::max()) {
                    // Store path information
                    path_info info;
                    info.total_distance = distances[j];
                    // Store intermediate nodes if needed
                    compressed_paths[i][j] = info;
                }
            }
            nodes_processed++;
        }
    }

    auto preprocessing_time = duration_cast<milliseconds>(high_resolution_clock::now() - start);
    cout << "Preprocessing time: " << preprocessing_time.count() << "ms" << endl;

    // Save compressed paths to binary file
    cout << "Saving path cache to binary file..." << endl;
    start = high_resolution_clock::now();
    
    if (save_compressed_paths_binary(binary_cache_file, compressed_paths)) {
        auto save_time = duration_cast<milliseconds>(high_resolution_clock::now() - start);
        cout << "Successfully saved path cache to " << binary_cache_file << endl;
        cout << "Save time: " << save_time.count() << "ms" << endl;
        cout << "Cached paths: " << nodes_processed << " source nodes" << endl;
        cout << "Total cache entries: " << compressed_paths.size() << endl;
    } else {
        cerr << "Failed to save path cache" << endl;
        return 1;
    }

    // Verify the binary file
    unordered_map<int, unordered_map<int, path_info>> loaded_paths;
    start = high_resolution_clock::now();
    
    if (load_compressed_paths_binary(binary_cache_file, loaded_paths)) {
        auto load_time = duration_cast<milliseconds>(high_resolution_clock::now() - start);
        cout << "Successfully verified binary cache file" << endl;
        cout << "Load time: " << load_time.count() << "ms" << endl;
    } else {
        cerr << "Failed to verify binary cache file" << endl;
        return 1;
    }

    return 0;
}