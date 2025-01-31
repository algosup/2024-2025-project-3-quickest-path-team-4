#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

struct transitionPath
{
    int startNode;  // Always an intersection node
    vector<pair<int, int>> transitionNodes;  // List of nodes with exactly 2 neighbors and their distance
    int totalDistance;  // Total distance from startNode to endNode
    pair <int, int> endNode;  // Can be another intersection node or a 1-neighbor node, with its distance
};

/* struct intersectionNode
{
    int node;
    vector<int> smallNeighbors;

} */

transitionPath* createTransitionPath(int start, vector <pair<int,int>> listTransition, pair<int,int> end)
{
    transitionPath* newPath = new transitionPath;

    newPath->startNode = start;

    for (int i = 0; i < listTransition.size(); i++)
    {
        newPath->transitionNodes.push_back({listTransition.at(i).first, listTransition.at(i).second});
    } 

    newPath->endNode.first = end.first;
    newPath->endNode.second = end.second;

    int pathTotal = 0;

    for (int i = 0; i < newPath->transitionNodes.size(); i++)
    {
        pathTotal += listTransition.at(i).second;
        cout << pathTotal << endl;
    } 

    newPath->totalDistance = pathTotal + newPath->endNode.second;
    
    return newPath;
}

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
        {5, {{5, 30}}},
        {6, {{1, 70}}},
        {7, {{1, 35}}},};

    //printAdjacencyList(adjacencyTest);

    int start = 1;

    int firstSolo = adjacencyTest[start][1].first;
    int firstSoloDist = adjacencyTest[start][1].second;

    int secondSolo = adjacencyTest[start][2].first;
    int secondSoloDist = adjacencyTest[start][2].second;

    int firstPath = adjacencyTest[start][0].first;
    int firstPathDist = adjacencyTest[start][0].second;

    int secondPath = adjacencyTest[2][1].first;
    int secondPathDist = adjacencyTest[2][1].second;

    int thirdPath = adjacencyTest[3][1].first;
    int thirdPathDist = adjacencyTest[3][1].second;

    int lastPath = adjacencyTest[4][1].first;
    int lastPathDist = adjacencyTest[4][1].second;

    pair<int, int> end = {lastPath, lastPathDist};
    
    vector<pair<int, int>> listTransition;
    listTransition.push_back({firstPath, firstPathDist});
    listTransition.push_back({secondPath, secondPathDist});
    listTransition.push_back({thirdPath, thirdPathDist});

    transitionPath* newPath = createTransitionPath(start, listTransition, end);

    cout << "path start = " << newPath->startNode << endl;
    for (int i = 0; i < newPath->transitionNodes.size(); i++)
    {
        cout << "transitionNode n " << i << " = " << newPath->transitionNodes.at(i).first << ", distance = " << newPath->transitionNodes.at(i).second << endl;
    }

    cout << "path end = " << newPath->endNode.first << ", distance = " << newPath->endNode.second << endl;

    cout << "total distance = " << newPath->totalDistance << endl;
    

    //GOAL: pathA, nodeStart, node2, dist1, node3, dist2, nodeEnd, dist3, pathDist

    return 0;
}