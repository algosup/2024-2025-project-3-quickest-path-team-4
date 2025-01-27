#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

struct WeightedEdge {
    int A;
    int B;
    int time;
};

using WeightedAdjList = std::unordered_map<int, std::vector<std::pair<int, int>>>;

// Function prototypes
bool buildWeightedAdjList(const std::string &csvFile, WeightedAdjList &adj, std::vector<WeightedEdge> &allEdges, std::vector<std::pair<int, int>> &selfLoops, std::unordered_set<int> &allNodes);
size_t bfsConnectivity(const WeightedAdjList &adj);
bool hasCycleUndirected(const WeightedAdjList &adj);
std::vector<int> findIsolatedNodes(const WeightedAdjList &adj, const std::unordered_set<int> &allNodes);
std::vector<WeightedEdge> findIsolatedEdges(const WeightedAdjList &adj, const std::vector<WeightedEdge> &allEdges);
void writeJsonFormat(const WeightedAdjList &adj, const std::string &filename);

void printSeparator() {
    std::cout << "\n=======================================\n";
}

bool isFileEmpty(const std::string& filename) {
    std::ifstream file(filename);
    return file.peek() == std::ifstream::traits_type::eof();
}

// Function to remove duplicate rows from the CSV file and identify duplicates
bool removeDuplicateRows(const std::string& filename, std::vector<std::tuple<int, int, int>>& edges, std::unordered_map<std::string, std::vector<int>>& duplicateRows) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open CSV file: " << filename << "\n";
        return false;
    }

    std::unordered_map<std::string, int> uniqueRows;
    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        ++lineNumber;
        if (uniqueRows.find(line) == uniqueRows.end()) {
            uniqueRows[line] = lineNumber;
            std::istringstream ss(line);
            int node1, node2, time;
            char comma;
            ss >> node1 >> comma >> node2 >> comma >> time;
            edges.emplace_back(node1, node2, time);
        } else {
            duplicateRows[line].push_back(uniqueRows[line]);
            duplicateRows[line].push_back(lineNumber);
        }
    }

    file.close();
    return true;
}

int main(int argc, char **argv) {
    
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <csv_file>\n";
        return 1;
    }

    printSeparator();

    std::string csvFile = argv[1];

    if (isFileEmpty(csvFile)) {
        std::cout << "CSV file is empty. No processing will be done.\n";
        printSeparator();
        return 0;
    }

    // Data structures
    WeightedAdjList adj;
    std::vector<WeightedEdge> allEdges;
    std::vector<std::pair<int, int>> selfLoops;
    std::unordered_set<int> allNodes;

    // Remove duplicate rows and build edges
    std::vector<std::tuple<int, int, int>> edges;
    std::unordered_map<std::string, std::vector<int>> duplicateRows;
    if (!removeDuplicateRows(csvFile, edges, duplicateRows)) {
        return 1;
    }

    // Print duplicate rows
    if (!duplicateRows.empty()) {
        std::cout << "Duplicate rows found:\n";
        for (const auto& entry : duplicateRows) {
            std::cout << "Duplicate row found => \"" << entry.first << "\" (lines ";
            for (size_t i = 0; i < entry.second.size(); ++i) {
                std::cout << entry.second[i];
                if (i + 1 < entry.second.size()) {
                    std::cout << " and ";
                }
            }
            std::cout << ")\n";
        }
    }

    // Build adjacency list and parse CSV
    if (!buildWeightedAdjList(csvFile, adj, allEdges, selfLoops, allNodes)) {
        return 1;
    }

    printSeparator();

    // Write adjacency list to JSON
    writeJsonFormat(adj, "adjaAndNode.json");

    printSeparator();

    // Basic stats
    std::cout << "Number of distinct nodes in adjacency: " << allNodes.size() << "\n";
    std::cout << "Number of edges read (excluding self-loops): " << allEdges.size() << "\n";
    std::cout << "Number of self-loops found: " << selfLoops.size() << "\n";

    printSeparator();

    // BFS connectivity check
    size_t visitedCount = bfsConnectivity(adj);
    if (visitedCount == allNodes.size()) {
        std::cout << "Graph is fully connected.\n";
    } else {
        std::cout << "Graph is NOT fully connected: visited only " << visitedCount << " of " << allNodes.size() << " nodes.\n";
    }

    printSeparator();

    // Cycle detection
    if (hasCycleUndirected(adj)) {
        std::cout << "Cycle found => Graph is not acyclic.\n";
    } else {
        std::cout << "No cycle found => Graph is acyclic.\n";
    }

    printSeparator();

    // Isolated nodes
    auto isolatedNodes = findIsolatedNodes(adj, allNodes);
    std::cout << "Number of isolated nodes (degree=0): " << isolatedNodes.size() << "\n";

    printSeparator();

    // Isolated edges
    auto isolatedEdges = findIsolatedEdges(adj, allEdges);
    std::cout << "Number of edges whose endpoints each have degree=1: " << isolatedEdges.size() << "\n";

    return 0;
}

bool buildWeightedAdjList(const std::string &csvFile, WeightedAdjList &adj, std::vector<WeightedEdge> &allEdges, std::vector<std::pair<int, int>> &selfLoops, std::unordered_set<int> &allNodes) {
    std::ifstream in(csvFile);
    if (!in.is_open()) {
        std::cerr << "Error opening file: " << csvFile << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string tokenA, tokenB, tokenTime;

        // Token validation
        if (!std::getline(ss, tokenA, ',') || !std::getline(ss, tokenB, ',') || !std::getline(ss, tokenTime, ',')) {
            std::cerr << "Error: Malformed row (missing fields) => " << line << std::endl;
            continue;
        }

        // Check for extra columns
        std::string extraToken;
        if (std::getline(ss, extraToken, ',')) {
            std::cerr << "Error: Extra columns detected => " << line << std::endl;
            continue;
        }

        try {
            int A = std::stoi(tokenA);
            int B = std::stoi(tokenB);
            int t = std::stoi(tokenTime);

            // Add to all nodes
            allNodes.insert(A);
            allNodes.insert(B);

            if (A == B) {
                selfLoops.push_back({A, t});
                continue;
            }

            allEdges.push_back({A, B, t});
            adj[A].push_back({B, t});
            adj[B].push_back({A, t});
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: Invalid value in row => " << line << "\n";
            continue;
        } catch (const std::out_of_range &e) {
            std::cerr << "Error: Value out of range in row => " << line << "\n";
            continue;
        }
    }

    return true;
}

size_t bfsConnectivity(const WeightedAdjList &adj) {
    if (adj.empty()) return 0;

    std::unordered_set<int> visited;
    std::queue<int> Q;
    Q.push(adj.begin()->first);
    visited.insert(adj.begin()->first);

    while (!Q.empty()) {
        int node = Q.front();
        Q.pop();

        for (const auto &nbr : adj.at(node)) {
            if (visited.find(nbr.first) == visited.end()) {
                visited.insert(nbr.first);
                Q.push(nbr.first);
            }
        }
    }

    return visited.size();
}

bool hasCycleUndirected(const WeightedAdjList &adj) {
    std::unordered_set<int> visited;

    std::function<bool(int, int)> dfs = [&](int node, int parent) {
        visited.insert(node);
        for (const auto &nbr : adj.at(node)) {
            if (visited.find(nbr.first) == visited.end()) {
                if (dfs(nbr.first, node)) return true;
            } else if (nbr.first != parent) {
                return true;
            }
        }
        return false;
    };

    for (const auto &node : adj) {
        if (visited.find(node.first) == visited.end()) {
            if (dfs(node.first, -1)) return true;
        }
    }

    return false;
}

std::vector<int> findIsolatedNodes(const WeightedAdjList &adj, const std::unordered_set<int> &allNodes) {
    std::vector<int> isolated;
    for (const int node : allNodes) {
        if (adj.find(node) == adj.end() || adj.at(node).empty()) {
            isolated.push_back(node);
        }
    }
    return isolated;
}

std::vector<WeightedEdge> findIsolatedEdges(const WeightedAdjList &adj, const std::vector<WeightedEdge> &allEdges) {
    std::vector<WeightedEdge> isolatedEdges;
    std::unordered_map<int, int> degree;

    for (const auto &kv : adj) {
        degree[kv.first] = kv.second.size();
    }

    for (const auto &edge : allEdges) {
        if (degree[edge.A] == 1 && degree[edge.B] == 1) {
            isolatedEdges.push_back(edge);
        }
    }

    return isolatedEdges;
}

void writeJsonFormat(const WeightedAdjList &adj, const std::string &filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    out << "{\n";
    for (auto it = adj.begin(); it != adj.end(); ++it) {
        out << "  \"" << it->first << "\": [";
        for (size_t i = 0; i < it->second.size(); ++i) {
            out << "[" << it->second[i].first << ", " << it->second[i].second << "]";
            if (i + 1 < it->second.size()) out << ", ";
        }
        out << "]";
        if (std::next(it) != adj.end()) out << ",";
        out << "\n";
    }
    out << "}\n";

    std::cout << "Wrote adjacency to " << filename << " in JSON-like format.\n";

}
