#include <iostream>
#include <fstream>
#include <unordered_set>
#include <random>
#include <ctime>
#include <algorithm>

// A helper struct to identify an undirected edge uniquely (A < B).
struct UndirectedEdge {
    int A, B;     // A < B always
    int weight;
};

// Needed so we can store UndirectedEdge in an unordered_set without duplicates.
struct EdgeHash {
    std::size_t operator()(const UndirectedEdge &e) const {
        // Combine A, B, and weight in a simple way.
        // You can use something more advanced if you like.
        // This just prevents trivial collisions.
        auto h1 = std::hash<int>()(e.A);
        auto h2 = std::hash<int>()(e.B);
        auto h3 = std::hash<int>()(e.weight);
        // A standard combine approach:
        // (h1 ^ (h2 + large_prime + (h1 << 6) + (h1 >> 2))) ^ h3 ...
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2))
                  ^ h3;
    }
};

struct EdgeEqual {
    bool operator()(const UndirectedEdge &a, const UndirectedEdge &b) const {
        return (a.A == b.A && a.B == b.B && a.weight == b.weight);
    }
};

int main() 
{
    // PARAMETERS to tweak:
    int numNodes = 15;    // how many nodes total
    int numEdges = 100;   // how many edges to print
    int minWeight = 1;    // smallest 'Time'
    int maxWeight = 50;   // largest 'Time'

    // We'll label nodes from 1..numNodes for clarity
    // If you want more nodes, just increase numNodes.

    // Initialize random generator
    std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<int> nodeDist(1, numNodes);
    std::uniform_int_distribution<int> weightDist(minWeight, maxWeight);

    // We'll store edges in an unordered_set (no duplicates).
    std::unordered_set<UndirectedEdge, EdgeHash, EdgeEqual> edges;
    edges.reserve(numEdges);

    // 1) First, create a simple SPANNING TREE to ensure connectivity.
    //    We'll connect node i to i+1 for i=1..(numNodes-1).
    //    That yields (numNodes - 1) edges and guarantees at least
    //    there's one path between all nodes.
    for (int i = 1; i < numNodes; i++) {
        int A = i;
        int B = i + 1;
        // Make sure A < B
        if (B < A) std::swap(A, B);

        UndirectedEdge e;
        e.A = A;
        e.B = B;
        e.weight = weightDist(rng);

        edges.insert(e);
    }

    // 2) Add EXTRA RANDOM EDGES until we have 'numEdges' total.
    //    This should produce some cycles and cross-links.
    while (static_cast<int>(edges.size()) < numEdges) 
    {
        int A = nodeDist(rng);  // random node in [1..numNodes]
        int B = nodeDist(rng);  // another random node in same range

        // skip if it's a self-loop
        if (A == B) continue;

        // enforce A < B for undirected uniqueness
        if (B < A) std::swap(A, B);

        UndirectedEdge e;
        e.A = A;
        e.B = B;
        e.weight = weightDist(rng);

        // If it's new, it will be inserted; if it's a duplicate, it won't.
        edges.insert(e);
    }

    // 3) Now we have 'numEdges' edges (or slightly more if the spanning tree alone had duplicates,
    //    but that can't really happen the way we built it).
    //    Let's write them to a CSV file in the same format: A,B,Time
    std::ofstream out("graph_100.csv");
    if (!out.is_open()) {
        std::cerr << "Could not open 'graph_100.csv' for writing.\n";
        return 1;
    }

    // Just output them. No particular order is strictly required.
    // If you want them in ascending node order, you can put them in a vector
    // and sort. We'll just iterate the set.
    int count = 0;
    for (auto &e : edges) {
        out << e.A << "," << e.B << "," << e.weight << "\n";
        count++;
    }
    out.close();

    std::cout << "Wrote " << count << " edges to 'graph_100.csv' with " 
              << numNodes << " nodes.\n";

    return 0;
}
