// automatisation for testing 99 test
// the purpose is to analyse the performance of the different version of the algorithm

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <chrono>
#include "../algo/graph_data.h"
#include "../algo/loading.cpp"
#include "../algo/Dijkstra.cpp"
#include "../algo/preprocess.cpp"
#include <sys/stat.h>  // For mkdir()
#include <sys/types.h> // For stat()
#include <filesystem>  // C++17 for creating directories
using namespace std;
namespace fs = std::filesystem;

using namespace std;

struct TestCase {
    string testID;
    int source;
    int destination;
};

// Function to load test cases from CSV file
vector<TestCase> loadTestCases(const string &filename) {
    vector<TestCase> testCases;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error opening test cases file: " << filename << endl;
        return testCases;
    }

    while (getline(file, line)) {
        istringstream ss(line);
        string testID, sourceStr, destinationStr;

        // Read CSV columns
        if (!getline(ss, testID, ',') || !getline(ss, sourceStr, ',') || !getline(ss, destinationStr, ',')) {
            cerr << "Skipping invalid test case (missing values): " << line << endl;
            continue;
        }

        // Debug: Print parsed values
        cout << "Processing Test: " << testID << ", Source: " << sourceStr << ", Destination: " << destinationStr << endl;

        // Ensure values are numeric before conversion
        try {
            int source = stoi(sourceStr);
            int destination = stoi(destinationStr);
            testCases.push_back({testID, source, destination});
        } catch (const invalid_argument &e) {
            cerr << "Skipping invalid test case (non-numeric values): " << line << endl;
        } catch (const out_of_range &e) {
            cerr << "Skipping invalid test case (out of range values): " << line << endl;
        }
    }

    return testCases;
}

void ensureDirectoryExists(const string& dir) {
    if (!fs::exists(dir)) {
        cout << "Creating directory: " << dir << endl;
        fs::create_directories(dir);
    }
}

void runTestCases(const vector<TestCase> &testCases, const string &graphFile) {
    graph_data g_data = load_graph_data(graphFile);
    unordered_map<int, int> single_neighbors;
    preprocess(&g_data, &single_neighbors);
    unordered_map<int, int> distances;

    string resultDir = "../../qualityAssurance/testing/testResults/AL_019_V5";
    ensureDirectoryExists(resultDir); 

    ofstream summary(resultDir + "/results_summary.txt");
    if (!summary.is_open()) {
        cerr << "Error: Unable to open summary file for writing." << endl;
        return;
    }

    summary << "Test Summary\n===================\n";

    for (size_t i = 0; i < testCases.size(); ++i) {
        const auto &tc = testCases[i];

        string resultFile = resultDir + "/" + tc.testID + ".txt";
        ofstream result(resultFile);

        if (!result.is_open()) {
            cerr << "Error: Unable to open file for test case " << tc.testID << endl;
            continue;  // Skip this test if file cannot be opened
        }

        distances.clear();
        for (const auto &[node, _] : g_data.adjacency) {
            distances[node] = numeric_limits<int>::max();
        }
        distances[tc.source] = 0;

        auto start_time = chrono::steady_clock::now();
        auto resultPath = bidirectional_dijkstra(g_data, tc.source, tc.destination, &distances);
        auto stop_time = chrono::steady_clock::now();
        int exec_time = chrono::duration_cast<chrono::milliseconds>(stop_time - start_time).count();

        if (resultPath.has_value()) {
            result << "Test ID: " << tc.testID << "\n";
            result << "Source: " << tc.source << " Destination: " << tc.destination << "\n";
            result << "Path: ";
            for (int node : resultPath.value()) {
                result << node << " ";
            }
            result << "\nNodes Count: " << resultPath.value().size() << "\n";
            result << "Execution Time: " << exec_time << " ms\n";

            summary << "Test " << tc.testID << " | Nodes: " << resultPath.value().size() << " | Time: " << exec_time << " ms\n";
        } else {
            result << "Test ID: " << tc.testID << "\n";
            result << "No path found from " << tc.source << " to " << tc.destination << "\n";
            summary << "Test " << tc.testID << " | No Path Found\n";
        }
        result.close();
        cout << "Progress: " << (i + 1) << "/" << testCases.size() << "\r";
        cout.flush();
    }
    summary.close();
    cout << "\nAll tests completed. Results saved.\n";
}

int main() {
    string testFile =  "../../qualityAssurance/testing/testFile/testCases.csv";
    string graphFile = "../../qualityAssurance/testing/testFile/USA-roads.csv";

    vector<TestCase> testCases = loadTestCases(testFile);
    if (testCases.empty()) {
        cerr << "No valid test cases found. Exiting." << endl;
        return 1;
    }

    runTestCases(testCases, graphFile);

    return 0;
}
