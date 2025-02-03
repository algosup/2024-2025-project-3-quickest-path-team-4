#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Edge {
    int start;
    int target;
    int distance;
};

void loadGraphFromCSV(const string& csvFilename, Edge*& edges, int& edgeCount) {
    ifstream file(csvFilename);
    edgeCount = 0;
    
    if (!file) {
        cerr << "Error: Could not open " << csvFilename << endl;
        return;
    }

    edges = nullptr;
    int capacity = 10;
    edges = new Edge[capacity];
    string line;

    // Skip header line
    if (getline(file, line) && line.find("Current node") != string::npos) {
        cout << "Skipping header row: " << line << endl;
    }

    while (getline(file, line)) {
        Edge temp;
        if (sscanf(line.c_str(), "%d,%d,%d", &temp.start, &temp.target, &temp.distance) != 3) {
            cerr << "Error: Invalid line format -> " << line << endl;
            continue;
        }

        if (edgeCount == capacity) {
            capacity *= 2;
            Edge* newEdges = new Edge[capacity];
            for (int i = 0; i < edgeCount; i++) {
                newEdges[i] = edges[i];
            }
            delete[] edges;
            edges = newEdges;
        }
        edges[edgeCount++] = temp;
    }
    file.close();
}


void saveGraphToBinary(const string& binaryFilename, Edge* edges, int edgeCount) {
    ofstream file(binaryFilename, ios::binary);
    file.write(reinterpret_cast<const char*>(&edgeCount), sizeof(edgeCount));
    file.write(reinterpret_cast<const char*>(edges), edgeCount * sizeof(Edge));
    file.close();
}

int main() {
    Edge* edges = nullptr;
    int edgeCount;
    
    string csvFilename = "USA-roads.csv";
    string binaryFilename = "USA-roads.bin";
    
    cout << "Loading graph from CSV..." << endl;
    loadGraphFromCSV(csvFilename, edges, edgeCount);
    
    cout << "Total edges loaded: " << edgeCount << endl;
    for (int i = 0; i < edgeCount; i++) {
        cout << edges[i].start << " -> " << edges[i].target << " : " << edges[i].distance << endl;
    }
    
    cout << "Graph loaded. Saving to binary file..." << endl;
    saveGraphToBinary(binaryFilename, edges, edgeCount);
    cout << "Graph saved to " << binaryFilename << endl;
    
    delete[] edges;
    return 0;
}
