#include "binary_writer.h"
#include <iostream>
#include <fstream>
#include <string>
#include "csv_parser.h"

bool write_binary(const std::string& output_file, const GraphData& graph_data) {
    std::ofstream ofs(output_file, std::ios::binary);
    if (!ofs) {
        std::cerr << "Error opening output file: " << output_file << std::endl;
        return false;
    }

    // Write the number of intersections
    size_t num_intersections = graph_data.intersections.size();
    ofs.write(reinterpret_cast<const char*>(&num_intersections), sizeof(num_intersections));

    // Write the intersections
    for (const auto& intersection : graph_data.intersections) {
        ofs.write(reinterpret_cast<const char*>(&intersection), sizeof(intersection));
    }

    // Write the number of edges
    size_t num_edges = graph_data.edges.size();
    ofs.write(reinterpret_cast<const char*>(&num_edges), sizeof(num_edges));

    // Write the edges
    for (const auto& edge : graph_data.edges) {
        ofs.write(reinterpret_cast<const char*>(&edge), sizeof(edge));
    }

    // Write the number of nodes contained within intersection paths
    size_t num_nodes_in_paths = graph_data.nodes_in_paths.size();
    ofs.write(reinterpret_cast<const char*>(&num_nodes_in_paths), sizeof(num_nodes_in_paths));

    // Write the nodes contained within intersection paths
    for (const auto& node : graph_data.nodes_in_paths) {
        ofs.write(reinterpret_cast<const char*>(&node), sizeof(node));
    }

    ofs.close();
    return true;
}

#ifndef SERVER_MODE
int preprocess_main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_csv_file> <output_binary_file>" << std::endl;
        return 1;
    }

    // Specify the path to the CSV file in the server directory
    const std::string input_csv_file = std::string(argv[1]);
    // Specify the path to the output binary file in the server directory
    const std::string output_binary_file = "../" + std::string(argv[2]);

    // Debugging output to verify file paths
    std::cout << "Input CSV file: " << input_csv_file << std::endl;
    std::cout << "Output binary file: " << output_binary_file << std::endl;

    // Parse the CSV file to extract intersections, edges, and connecting nodes
    GraphData graph_data;
    if (!parse_csv(input_csv_file, graph_data)) {
        std::cerr << "Error parsing CSV file: " << input_csv_file << std::endl;
        return 1;
    }

    // Write the parsed data to a binary file
    if (!write_binary(output_binary_file, graph_data)) {
        std::cerr << "Error writing binary file: " << output_binary_file << std::endl;
        return 1;
    }

    std::cout << "Successfully processed " << input_csv_file << " and created " << output_binary_file << std::endl;
    return 0;
}
#endif