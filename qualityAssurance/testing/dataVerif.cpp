#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>  // for std::sort


struct WeightedEdge {
    int A;
    int B;
    int time;
};


// Weighted adjacency type: node -> list of (neighbor, time)
using WeightedAdjList = std::unordered_map<int, std::vector<std::pair<int,int>>>;

//
// 2) Build Weighted Adjacency (Reading CSV)
//

/**
 * Reads a CSV file of edges in the form:  A,B,Time
 * and stores them in a vector<WeightedEdge>.
 * Then builds an undirected WeightedAdjList:
 *    adj[A].push_back({B, time});
 *    adj[B].push_back({A, time});
 *
 * Also collects self-loops (A == B) if encountered, so you can handle them separately.
 */
bool buildWeightedAdjList(
    const std::string &csvFile,
    WeightedAdjList &adj,
    std::vector<WeightedEdge> &allEdges,
    std::vector<std::pair<int,int>> &selfLoops
)
{
    std::ifstream in(csvFile);
    if (!in.is_open()) {
        std::cerr << "Error opening file: " << csvFile << std::endl;
        return false;
    }

    long long lineCount = 0;
    std::string line;

    while (true) {
        if (!std::getline(in, line)) break;
        lineCount++;
        if (line.empty()) continue; // skip empty lines

        std::stringstream ss(line);
        std::string tokenA, tokenB, tokenTime;
        if (!std::getline(ss, tokenA, ',')) continue;
        if (!std::getline(ss, tokenB, ',')) continue;
        if (!std::getline(ss, tokenTime, ',')) continue;

        int A = std::stoi(tokenA);
        int B = std::stoi(tokenB);
        int t = std::stoi(tokenTime);

        // Check for self-loop
        if (A == B) {
            selfLoops.push_back({A, t});
            continue;  // skip adding to adjacency if you don't want them
        }

        // Store in allEdges
        allEdges.push_back({A, B, t});

        // Insert into adjacency, undirected => both directions
        adj[A].push_back({B, t});
        adj[B].push_back({A, t});
    }

    std::cout << "Finished reading " << lineCount << " lines.\n";
    return true;
}

//
// 3) BFS Connectivity
//

/**
 * BFS to count how many nodes are reachable from an arbitrary start node.
 * If the visited count < total number of nodes, the graph is disconnected.
 */
size_t bfsConnectivity(const WeightedAdjList &adj)
{
    if (adj.empty()) {
        return 0;
    }

    // Pick an arbitrary start node
    int startNode = adj.begin()->first;

    std::unordered_set<int> visited;
    std::queue<int> Q;

    visited.insert(startNode);
    Q.push(startNode);

    while (!Q.empty()) {
        int current = Q.front();
        Q.pop();

        // check neighbors
        const auto &nbrList = adj.at(current);
        for (auto &p : nbrList) {
            int nbr = p.first; // ignoring time for connectivity
            if (!visited.count(nbr)) {
                visited.insert(nbr);
                Q.push(nbr);
            }
        }
    }

    return visited.size();
}

//
// 4) Cycle Detection (DFS) in Undirected Graph
//

bool hasCycleUtil(
    int node,
    int parent,
    const WeightedAdjList &adj,
    std::unordered_set<int> &visited
)
{
    visited.insert(node);

    // for each neighbor
    for (auto &nbrPair : adj.at(node)) {
        int nbr = nbrPair.first;
        if (!visited.count(nbr)) {
            if (hasCycleUtil(nbr, node, adj, visited)) {
                return true;  // cycle found
            }
        }
        else if (nbr != parent) {
            // visited neighbor that isn't our parent => cycle
            return true;
        }
    }
    return false;
}

bool hasCycleUndirected(const WeightedAdjList &adj)
{
    std::unordered_set<int> visited;
    // We must check each connected component
    for (auto &kv : adj) {
        int node = kv.first;
        if (!visited.count(node)) {
            if (hasCycleUtil(node, -1, adj, visited)) {
                return true; // cycle found
            }
        }
    }
    return false;
}

//
// 5) Find Isolated Nodes
//

/**
 * A node is isolated (degree=0) if it has no neighbors.
 */
std::vector<int> findIsolatedNodes(const WeightedAdjList &adj)
{
    std::vector<int> isolated;
    isolated.reserve(adj.size());

    for (auto &kv : adj) {
        int node = kv.first;
        const auto &nbrs = kv.second;
        if (nbrs.empty()) {
            isolated.push_back(node);
        }
    }
    return isolated;
}

//
// 6) Find "Isolated Edges" => edges where both endpoints have degree=1
//

std::vector<WeightedEdge> findIsolatedEdges(
    const WeightedAdjList &adj,
    const std::vector<WeightedEdge> &allEdges
)
{
    std::vector<WeightedEdge> isolatedEdges;
    isolatedEdges.reserve(allEdges.size());

    // compute degree (i.e., number of neighbors) for each node
    std::unordered_map<int,int> degree;
    degree.reserve(adj.size());
    for (auto &kv : adj) {
        degree[kv.first] = kv.second.size();
    }

    // check each edge
    for (auto &e : allEdges) {
        if (degree[e.A] == 1 && degree[e.B] == 1) {
            // both endpoints are degree=1 => isolated edge
            isolatedEdges.push_back(e);
        }
    }
    return isolatedEdges;
}


/**
 * For each node, we print:
 *   "X":[[nbr1,time1],[nbr2,time2],...],
 */
void writeJsonFormat(
    const WeightedAdjList &adj,
    const std::string &filename
)
{
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Error: cannot open " << filename << " for writing.\n";
        return;
    }

    // gather nodes and sort them
    std::vector<int> nodes;
    nodes.reserve(adj.size());
    for (auto &kv : adj) {
        nodes.push_back(kv.first);
    }
    std::sort(nodes.begin(), nodes.end());

    out << "{\n";

    // iterate each node in ascending order
    for (size_t i = 0; i < nodes.size(); i++) {
        int node = nodes[i];
        out << "  \"" << node << "\":[";   // "1":[

        // get the neighbor list
        const auto &nbrList = adj.at(node);

        // optional: sort neighbors by ID
        std::vector<std::pair<int,int>> sortedNbrs(nbrList.begin(), nbrList.end());
        std::sort(sortedNbrs.begin(), sortedNbrs.end(),
                  [](auto &a, auto &b){
                      return a.first < b.first; 
                  });

        // Print array of [nbr,time] pairs
        out << "["; 
        for (size_t j = 0; j < sortedNbrs.size(); j++) {
            int nbr  = sortedNbrs[j].first;
            int time = sortedNbrs[j].second;
            out << nbr << "," << time;
            if (j + 1 < sortedNbrs.size()) {
                out << "],[";
            }
        }
        out << "]"; // close last pair

        out << "]"; // close this node's array

        // if not the last node, put a comma
        if (i + 1 < nodes.size()) {
            out << ",";
        }
        out << "\n";
    }

    out << "}\n";
    out.close();

    std::cout << "Wrote adjacency to " << filename 
              << " in JSON-like format.\n";
}

//
// 8) Main
//

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " edges.csv\n";
        return 1;
    }

    std::string csvFile = argv[1];

    // Weighted adjacency
    WeightedAdjList adj;
    adj.reserve(10000000); // optional

    // Store all edges
    std::vector<WeightedEdge> allEdges;
    allEdges.reserve(24000000);

    // Self-loops
    std::vector<std::pair<int,int>> selfLoops;

    // 1) Build adjacency from CSV
    if (!buildWeightedAdjList(csvFile, adj, allEdges, selfLoops)) {
        return 1; // error reading
    }

    // 2) Write adjacency in the JSON-like format 
    writeJsonFormat(adj, "sortedData.json");

    // 3) Basic stats
    std::cout << "Number of distinct nodes in adjacency: " << adj.size() << "\n";
    std::cout << "Number of edges read (excluding self-loops): " << allEdges.size() << "\n";
    std::cout << "Number of self-loops found: " << selfLoops.size() << "\n\n";

    // 4) BFS connectivity
    size_t visitedCount = bfsConnectivity(adj);
    if (visitedCount == adj.size()) {
        std::cout << "Graph is fully connected.\n";
    } else {
        std::cout << "Graph is NOT fully connected: visited only "
                  << visitedCount << " of " << adj.size() << " nodes.\n";
    }

    // 5) Cycle detection
    bool cycleFound = hasCycleUndirected(adj);
    if (cycleFound) {
        std::cout << "Cycle found => Graph is not acyclic.\n";
    } else {
        std::cout << "No cycle found => Graph is acyclic (a tree if connected).\n";
    }

    // 6) Isolated nodes
    auto isolatedNodes = findIsolatedNodes(adj);
    std::cout << "Number of isolated nodes (degree=0): " 
              << isolatedNodes.size() << "\n";

    // 7) Isolated edges
    auto isolatedEdges = findIsolatedEdges(adj, allEdges);
    std::cout << "Number of edges whose endpoints each have degree=1: "
              << isolatedEdges.size() << "\n";

    // Done
    return 0;
}
