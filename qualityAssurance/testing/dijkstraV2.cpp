// Dijkstra Algorithm (Version 1) - C++20

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <optional>
#include <chrono>  // For measuring execution time
#include <ranges>  // C++20 ranges
#include <stack>

using namespace std;

// Struct to represent a road connection
struct Edge {
    int to, time;
};

// Struct to represent a priority queue element
struct Node {
    int id, time;
    bool operator>(const Node& other) const {
        return time > other.time;
    }
};

// Function to load the CSV file and build the graph
unordered_map<int, vector<Edge>> loadGraph(const string& filename) {
    unordered_map<int, vector<Edge>> graph;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return graph;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        int landmarkA, landmarkB, time;

        // Read CSV values
        getline(ss, item, ','); landmarkA = stoi(item);
        getline(ss, item, ','); landmarkB = stoi(item);
        getline(ss, item, ','); time = stoi(item);

        // Add bidirectional edges
        graph[landmarkA].emplace_back(Edge{landmarkB, time});
        graph[landmarkB].emplace_back(Edge{landmarkA, time});
    }

    file.close();
    return graph;
}

// Function to find the shortest path using Dijkstra's Algorithm
optional<tuple<int, vector<int>, int>> findShortestPath(
    const unordered_map<int, vector<Edge>>& graph, int start, int end) {
    
    unordered_map<int, int> minTime;
    unordered_map<int, int> previousNode; // To reconstruct the path
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    // Initialize all nodes with "infinity" time
    for (const auto& [node, _] : graph) {
        minTime[node] = numeric_limits<int>::max();
    }

    // Start measuring execution time
    auto start_time = chrono::high_resolution_clock::now();

    // Start from the source
    minTime[start] = 0;
    pq.push({start, 0});
    previousNode[start] = -1; // No predecessor for the start node

    while (!pq.empty()) {
        auto [currentNode, currentTime] = pq.top();
        pq.pop();

        // If we reached the destination, reconstruct the path
        if (currentNode == end) {
            vector<int> path;
            for (int node = end; node != -1; node = previousNode[node]) {
                path.push_back(node);
            }
            reverse(path.begin(), path.end());

            // End measuring execution time
            auto stop_time = chrono::high_resolution_clock::now();
            int exec_time = chrono::duration_cast<chrono::milliseconds>(stop_time - start_time).count();

            return make_tuple(currentTime, path, exec_time);
        }

        // Visit all neighbors
        for (const auto& [nextNode, travelTime] : graph.at(currentNode)) {
            int newTime = currentTime + travelTime;
            if (newTime < minTime[nextNode]) {
                minTime[nextNode] = newTime;
                previousNode[nextNode] = currentNode; // Track the path
                pq.push({nextNode, newTime});
            }
        }
    }

    return nullopt;  // No path found
}

// Main function
int main() {
    string filename = "../../src/algorithm/USA-roads.csv";
    auto graph = loadGraph(filename);

    if (graph.empty()) {
        cerr << "Error: No data loaded. Please check the file." << endl;
        return 1;
    }

    while (true) {
        int pointA, pointB;
        cout << "Enter the ID of Landmark A: ";
        cin >> pointA;
        cout << "Enter the ID of Landmark B: ";
        cin >> pointB;

        // Calculate the shortest path
        auto result = findShortestPath(graph, pointA, pointB);

        // Output the result
        if (result) {
            auto [shortestTime, path, exec_time] = result.value();
            cout << "The shortest time between Landmark " << pointA << " and Landmark " << pointB << " is: " 
                 << shortestTime << " units." << endl;
            // cout << "Shortest path: ";
            // for (int node : path) {
            //     cout << node << " -> ";
            // }
            // cout << "END" << endl;
            cout << "Number of nodes in shortest path: " << path.size() << endl;
            cout << "Execution Time: " << exec_time << " ms" << endl;
        } else {
            cout << "No path exists between Landmark " << pointA << " and Landmark " << pointB << "." << endl;
        }
    }

    return 0;
}
