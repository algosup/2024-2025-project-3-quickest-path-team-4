#include "graph_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

std::optional<GraphData> GraphLoader::load_from_csv(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << std::endl;
        return std::nullopt;
    }

    // Pre-allocate buffer for reading
    const size_t BUFFER_SIZE = 1024 * 1024; // 1MB buffer
    std::vector<char> buffer(BUFFER_SIZE);
    file.rdbuf()->pubsetbuf(buffer.data(), BUFFER_SIZE);

    GraphData graph;
    std::string line;
    int line_number = 0;
    std::vector<std::tuple<int, int, int>> edges;
    edges.reserve(1000000); // Reserve space for 1M edges initially

    try {
        while (std::getline(file, line)) {
            line_number++;
            std::stringstream ss(line);
            int node1, node2, cost;
            char comma;

            if (!(ss >> node1 >> comma >> node2 >> comma >> cost)) {
                std::cerr << "Warning: Invalid format at line " << line_number << std::endl;
                continue;
            }

            if (node1 < 0 || node2 < 0 || cost < 0) {
                std::cerr << "Warning: Invalid values at line " << line_number << std::endl;
                continue;
            }

            edges.emplace_back(node1, node2, cost);
        }

        // Sort edges by source node for better locality
        std::sort(edges.begin(), edges.end());

        // Batch add edges
        for (const auto& [node1, node2, cost] : edges) {
            graph.add_edge(node1, node2, cost);
        }

        std::cout << "Graph loaded successfully: "
              << graph.size() << " nodes, "  // Use size() for node count
              << graph.get_edge_count() << " edges" << std::endl;
              
        return graph;
    }
    catch (const std::exception& e) {
        std::cerr << "Error while loading graph: " << e.what() << std::endl;
        return std::nullopt;
    }
}

bool GraphLoader::save_to_binary(const GraphData& graph, const std::string& file_path) {
    std::ofstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    // Implementation for binary saving
    // This is a placeholder - implement actual binary saving if needed
    return true;
}

std::optional<GraphData> GraphLoader::load_from_binary(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        return std::nullopt;
    }

    // Implementation for binary loading
    // This is a placeholder - implement actual binary loading if needed
    return std::nullopt;
}