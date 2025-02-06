#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include "graph_data.h"
#include "loading.h"
//#include "preprocess.h"
#include "Bidirectional_Astar.h"
//#include "save_load_binary.h"

using namespace std;

int main() {
    string file_path = "USA-roads.csv";
    string compressed_paths_file = "compressed_paths.bin";
    //are_extremities_singles are_they;

    // Load the graph data
    graph_data g_data = load_graph_data(file_path);

    // Load compressed paths from binary file
    //unordered_map<int, unordered_map<int, path_info>> compressed_paths;
    //if (!load_compressed_paths_binary(compressed_paths_file, compressed_paths)) {
    //    cerr << "Failed to load compressed paths from binary file. Proceeding without precomputed paths." << endl;
    //}

    // Preprocess the graph
    unordered_map<int, int> single_neighbors;
    //preprocess(&g_data, &single_neighbors, compressed_paths);

    while (true) {
        int start, end;
        vector<int> distances(g_data.adjacency.size(), numeric_limits<int>::max());
        cout << endl;
        cout << "######################################################" << endl;;
        cout << endl;
        cout << "Road Runner is Ready!" << endl;
        cout << "Start node: ";

// Input validation for start node
        while (!(cin >> start)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer for the start node: ";
            continue;
        }

// Input validation for end node
        cout << "End node: ";
        while (!(cin >> end)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer for the end node: ";
            continue;
        }

        int true_start = start;
        int true_end = end;
        distances[start] = 0;

        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        //check_single_start_or_end(&start, &end, &single_neighbors, &are_they);
        cout << "Processing." << endl;

// Find all explored nodes using Bidirectional A*
        auto result = bidirectional_astar(g_data, start, end, distances);
        chrono::steady_clock::time_point stop = chrono::steady_clock::now();

        if (result.has_value()) {
            cout << "Explored nodes: ";
            for (int node : result.value()) {
                cout << node << " > ";
            }
            cout << endl;
        } else {
            cout << "No path found from " << start << " to " << end << endl;
        }

        cout << "Execution Time = " << chrono::duration_cast<chrono::milliseconds>(stop - begin).count() << "[ms]" << endl;
        cout << "Total explored nodes: " << result.value().size() << endl;
        char choice;
        cout << "Do you want to find another path? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            break;
        } else {
            cout << endl;
            cout << "######################################################" << endl;;
            cout << endl;
            continue;
        }
        }

    return 0;
}