#include <iostream>
#include <fstream>
#include <unordered_set>
#include <random>

using namespace std;

const int TOTAL_NODES = 23947347;
const int NUM_TESTS = 101;
const string OUTPUT_FILE = "test_cases.csv";

// Custom hash function for unordered_set with pairs
struct PairHash {
    template <typename T1, typename T2>
    size_t operator()(const pair<T1, T2> &p) const {
        return hash<T1>()(p.first) ^ (hash<T2>()(p.second) << 1);
    }
};

int main() {
    // Use random device to generate random numbers
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, TOTAL_NODES);

    unordered_set<pair<int, int>, PairHash> usedPairs;
    ofstream file(OUTPUT_FILE);

    if (!file.is_open()) {
        cerr << "Error: Cannot open output file!\n";
        return 1;
    }

    file << "Test ID, Source, Destination\n";

    for (int i = 1; i < NUM_TESTS; ++i) {
        int source, destination;
        do {
            source = dist(gen);
            destination = dist(gen);
        } while (source == destination || usedPairs.count({source, destination}));

        usedPairs.insert({source, destination});
        // | AL_019_01 | 1         | 2           | 2               | [AL_019_01](./testing/testingResuts/AL_019_01) |
        // file << "| AL_019_" << i << "|" << source << "|" << destination << "||[AL_019_" << i << "](./testing/testingResuts/AL_019_" << i << ")|" << "\n";
        // | **AL_019_01** |||||
        // file << "| **AL_019_" << i << "** |||||" << "\n";
        file << "AL_019_" << i << "," << source << "," << destination << "\n";
    }

    file.close();
    cout << "Generated " << NUM_TESTS << " test cases in " << OUTPUT_FILE << "\n";
    return 0;
}
