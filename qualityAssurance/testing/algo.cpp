#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

using namespace std;

// Struct to represent a road connection
struct Edge {
    int to;
    int time;
    Edge(int t, int tm) : to(t), time(tm) {}
};

// Struct to represent a priority queue element
struct Node {
    int id;
    int time;
    Node(int i, int t) : id(i), time(t) {}

    bool operator>(const Node& other) const {
        return time > other.time;
    }
};

// Function to load the CSV file and build the graph
unordered_map<int, vector<Edge> > loadGraph(const string& filename) {
    unordered_map<int, vector<Edge> > graph;
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

        // Read Landmark A
        getline(ss, item, ',');
        landmarkA = stoi(item);

        // Read Landmark B
        getline(ss, item, ',');
        landmarkB = stoi(item);

        // Read Time
        getline(ss, item, ',');
        time = stoi(item);

        // Add bidirectional edges
        graph[landmarkA].push_back(Edge(landmarkB, time));  // Constructor-style initialization
        graph[landmarkB].push_back(Edge(landmarkA, time));  // Constructor-style initialization
    }

    file.close();
    return graph;
}

// Function to find the shortest path using Dijkstra's Algorithm
int findShortestPath(const unordered_map<int, vector<Edge> >& graph, int start, int end) {
    unordered_map<int, int> minTime;  // Stores the shortest time to reach each node
    priority_queue<Node, vector<Node>, greater<Node> > pq;  // Min-heap priority queue

    // Initialize all nodes with "infinity" time
    for (unordered_map<int, vector<Edge> >::const_iterator it = graph.begin(); it != graph.end(); ++it) {
        minTime[it->first] = numeric_limits<int>::max();
    }

    // Start from the source
    minTime[start] = 0;
    pq.push(Node(start, 0));  // Constructor-style initialization

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int currentNode = current.id;
        int currentTime = current.time;

        // If we reached the destination, return the time
        if (currentNode == end) {
            return currentTime;
        }

        // Visit all neighbors of the current node
        for (const auto& edge : graph.at(currentNode)) {
            int nextNode = edge.to;
            int newTime = currentTime + edge.time;

            // If a faster path is found, update and push to the priority queue
            if (newTime < minTime[nextNode]) {
                minTime[nextNode] = newTime;
                pq.push(Node(nextNode, newTime));  // Constructor-style initialization
            }
        }
    }

    // If no path exists, return -1
    return -1;
}

// Main function
int main() {
    string filename = "USA-roads.csv";
    auto graph = loadGraph(filename);

    if (graph.empty()) {
        cerr << "Error: No data loaded. Please check the file." << endl;
        return 1;
    }

    while(true){
        // Get user input for points A and B
    int pointA, pointB;
    cout << "Enter the ID of Landmark A: ";
    cin >> pointA;
    cout << "Enter the ID of Landmark B: ";
    cin >> pointB;

    // Calculate the shortest path
    int shortestTime = findShortestPath(graph, pointA, pointB);

    // Output the result
    if (shortestTime != -1) {
        cout << "The shortest time between Landmark " << pointA
             << " and Landmark " << pointB << " is: " << shortestTime << " units." << endl;
    } else {
        cout << "No path exists between Landmark " << pointA << " and Landmark " << pointB << "." << endl;
    }
    }
    

    return 0;
}