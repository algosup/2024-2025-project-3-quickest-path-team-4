#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include "graph_data.h"
#include "loading.cpp"
#include "Bidirectional_Astar.cpp"
#include "preprocess.cpp"

using namespace std;

// BFS to precompute distances from landmarks
void bfs(const graph_data& graph, int start, vector<int>& distances) {
    queue<int> q;
    q.push(start);
    distances[start] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (const auto& [neighbor, weight] : graph.adjacency[current]) {
            if (distances[neighbor] == numeric_limits<int>::max()) {
                distances[neighbor] = distances[current] + 1;
                q.push(neighbor);
            }
        }
    }
}

// Precompute distances from landmarks
vector<vector<int>> precompute_landmark_distances(const graph_data& graph, const vector<int>& landmarks) {
    vector<vector<int>> landmark_distances(landmarks.size(), vector<int>(graph.adjacency.size(), numeric_limits<int>::max()));

    for (size_t i = 0; i < landmarks.size(); ++i) {
        bfs(graph, landmarks[i], landmark_distances[i]);
    }

    return landmark_distances;
}

// Select landmarks using Farthest-First Traversal
vector<int> select_landmarks(const graph_data& graph, int num_landmarks) {
    vector<int> landmarks;
    vector<int> distances(graph.adjacency.size(), numeric_limits<int>::max());
    int farthest_node = 0;  // Start with node 0

    for (int i = 0; i < num_landmarks; ++i) {
        landmarks.push_back(farthest_node);
        bfs(graph, farthest_node, distances);

        // Find the farthest node from the current landmarks
        farthest_node = max_element(distances.begin(), distances.end()) - distances.begin();
    }

    return landmarks;
}

int main() {
    string file_path = "USA-roads.csv";
    are_extremities_singles are_they;

    // Load the graph data
    graph_data g_data = load_graph_data(file_path);

    // Preprocess the graph
    unordered_map<int, int> single_neighbors;
    preprocess(&g_data, &single_neighbors);

    // Select landmarks and precompute distances
    int num_landmarks = 5;  // Adjust as needed
    vector<int> landmarks = select_landmarks(g_data, num_landmarks);
    vector<vector<int>> landmark_distances = precompute_landmark_distances(g_data, landmarks);

    while (true) {
        int start, end;
        vector<int> distances(g_data.adjacency.size(), numeric_limits<int>::max());

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

        // Find the shortest path using Bidirectional A*
        auto result = bidirectional_astar(g_data, start, end, distances, landmark_distances);

        chrono::steady_clock::time_point stop = chrono::steady_clock::now();

        if (result.has_value()) {
            if (are_they.is_start_single) {
                result.value().insert(result.value().begin(), start);
            }
            if (are_they.is_end_single) {
                result.value().push_back(end);
            }

            cout << "Shortest path from " << true_start << " to " << true_end << ": " << endl;
            for (int i = 0; i < result.value().size(); i++) {
                cout << result.value()[i] << " > ";
                if (result.value()[i] == true_end) {
                    cout << endl;
                    break;
                }
            }
        } else {
            cout << "No path found from " << start << " to " << end << endl;
            break;
        }

        cout << "Loading Time = " << chrono::duration_cast<chrono::milliseconds>(stop - begin).count() << "[ms]" << endl;
        cout << "Nodes: " << result.value().size() << endl;

        char choice;
        cout << "Do you want to find another path? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            break;
        }
    }

    return 0;
}