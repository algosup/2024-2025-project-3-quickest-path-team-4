#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <limits>

using namespace std;

using Graph = unordered_map<int, vector<int>>;

// Function to load the CSV file into an adjacency list
bool loadGraphFromCSV(const string& filename, Graph &graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open CSV file " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int A, B, time;
        char comma;

        if (!(ss >> A >> comma >> B >> comma >> time)) {
            cerr << "Error: Malformed line => " << line << endl;
            continue;
        }

        graph[A].push_back(B);
        graph[B].push_back(A);
    }

    file.close();
    return true;
}

// BFS function to find the farthest node from a given start node
pair<int, int> bfsFarthestNode(const Graph &graph, int start) {
    unordered_map<int, int> distance;
    queue<int> q;
    
    distance[start] = 0;
    q.push(start);

    int farthestNode = start;
    int maxDist = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : graph.at(node)) {
            if (distance.find(neighbor) == distance.end()) {
                distance[neighbor] = distance[node] + 1;
                q.push(neighbor);
                if (distance[neighbor] > maxDist) {
                    maxDist = distance[neighbor];
                    farthestNode = neighbor;
                }
            }
        }
    }

    return {farthestNode, maxDist};
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <csv_file>\n";
        return 1;
    }

    string csvFile = argv[1];
    Graph graph;

    cout << "Loading graph from CSV file..." << endl;
    if (!loadGraphFromCSV(csvFile, graph)) {
        return 1;
    }
    cout << "Graph loaded with " << graph.size() << " nodes." << endl;

    // Step 1: Run BFS from an arbitrary node
    int startNode = graph.begin()->first;
    cout << "Finding farthest node from " << startNode << "..." << endl;
    auto [firstFarthestNode, dist1] = bfsFarthestNode(graph, startNode);
    
    // Step 2: Run BFS from the farthest node found
    cout << "Finding farthest node from " << firstFarthestNode << "..." << endl;
    auto [secondFarthestNode, dist2] = bfsFarthestNode(graph, firstFarthestNode);

    // Output the result
    cout << "Most distant nodes for Dijkstra test: " << firstFarthestNode << " -> " << secondFarthestNode << endl;
    cout << "Shortest path between them has " << dist2 << " nodes." << endl;

    return 0;
}
