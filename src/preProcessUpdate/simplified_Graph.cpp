#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

struct transitionPath
{
    int startNode;  // Always an intersection node
    vector<int> transitionNodes;  // List of nodes with exactly 2 neighbors
    vector<int> distances;  // Distance between each consecutive transition node
    int totalDistance;  // Total distance from startNode to endNode
    int endNode;  // Can be another intersection node or a 1-neighbor node

};

void printAdjacency(int node, unordered_map<int, vector<pair<int, int>>> &adjacency)
{
    if (adjacency.find(node) == adjacency.end())
    {
        cout << "Node " << node << " does not exist in the graph.\n";
        return;
    }

    cout << "Adjacency list of node " << node << ": ";
    for (const auto &[neighbor, cost] : adjacency[node])
    {
        cout << "(" << neighbor << ", " << cost << ") ";
    }
    cout << endl;
}

void printAdjacencyList(const unordered_map<int, vector<pair<int, int>>> &adjacency)
{
    for (const auto &[node, neighbors] : adjacency)
    {
        printAdjacency(node, const_cast<unordered_map<int, vector<pair<int, int>>> &>(adjacency));
    }
}
int main()
{
    unordered_map<int, vector<pair<int, int>>> adjacencyTest = {
        {1, {{2, 20}, {6, 70}, {7, 35}}},
        {2, {{1, 20}, {3, 30}}},
        {3, {{2, 30}, {4, 12}}},
        {4, {{3, 12}, {5, 30}}},
        {5, {{5, 30}}}};

    printAdjacencyList(adjacencyTest);

    cout << "TEST" << endl;

   transitionPath* newPath = new transitionPath;

   // Access the first node in adjacencyTest (node 1)
    auto firstNode = adjacencyTest.begin();  // Get the first node as iterator
    newPath->startNode = firstNode->first;  // Assign the first node's key (1 in this case)
    
    cout << "Start node: " << newPath->startNode << endl;

    // If you want to print the adjacency list of the first node
    printAdjacency(newPath->startNode, adjacencyTest);


    //GOAL: pathA, nodeStart, node2, dist1, node3, dist2, nodeEnd, dist3, pathDist

    return 0;
}