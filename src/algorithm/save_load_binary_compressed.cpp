#include "save_load_binary_compressed.h"
#include <fstream>
#include <iostream>

// Save compressed paths to a binary file
void save_compressed_paths_binary(const std::string& file_path, const std::unordered_map<int, std::unordered_map<int, path_info>>& compressed_paths) {
    std::ofstream ofs(file_path, std::ios::binary);
    if (!ofs) {
        std::cerr << "Error: Could not open file for writing: " << file_path << std::endl;
        return;
    }

    // Write the number of start nodes
    size_t num_start_nodes = compressed_paths.size();
    ofs.write(reinterpret_cast<const char*>(&num_start_nodes), sizeof(num_start_nodes));

    for (const auto& [start, end_map] : compressed_paths) {
        // Write the start node
        ofs.write(reinterpret_cast<const char*>(&start), sizeof(start));

        // Write the number of end nodes
        size_t num_end_nodes = end_map.size();
        ofs.write(reinterpret_cast<const char*>(&num_end_nodes), sizeof(num_end_nodes));

        for (const auto& [end, info] : end_map) {
            // Write the end node
            ofs.write(reinterpret_cast<const char*>(&end), sizeof(end));

            // Write the total distance
            ofs.write(reinterpret_cast<const char*>(&info.total_distance), sizeof(info.total_distance));

            // Write the number of intermediate nodes
            size_t num_intermediate_nodes = info.intermediate_nodes.size();
            ofs.write(reinterpret_cast<const char*>(&num_intermediate_nodes), sizeof(num_intermediate_nodes));

            // Write the intermediate nodes
            ofs.write(reinterpret_cast<const char*>(info.intermediate_nodes.data()), num_intermediate_nodes * sizeof(int));
        }
    }

    std::cout << "Saved compressed paths to binary file: " << file_path << std::endl;
}

// Load compressed paths from a binary file
bool load_compressed_paths_binary(const std::string& file_path, std::unordered_map<int, std::unordered_map<int, path_info>>& compressed_paths) {
    std::ifstream ifs(file_path, std::ios::binary);
    if (!ifs) {
        std::cerr << "Error: Could not open file for reading: " << file_path << std::endl;
        return false;
    }

    // Read the number of start nodes
    size_t num_start_nodes;
    ifs.read(reinterpret_cast<char*>(&num_start_nodes), sizeof(num_start_nodes));

    for (size_t i = 0; i < num_start_nodes; ++i) {
        // Read the start node
        int start;
        ifs.read(reinterpret_cast<char*>(&start), sizeof(start));

        // Read the number of end nodes
        size_t num_end_nodes;
        ifs.read(reinterpret_cast<char*>(&num_end_nodes), sizeof(num_end_nodes));

        for (size_t j = 0; j < num_end_nodes; ++j) {
            // Read the end node
            int end;
            ifs.read(reinterpret_cast<char*>(&end), sizeof(end));

            // Read the total distance
            int total_distance;
            ifs.read(reinterpret_cast<char*>(&total_distance), sizeof(total_distance));

            // Read the number of intermediate nodes
            size_t num_intermediate_nodes;
            ifs.read(reinterpret_cast<char*>(&num_intermediate_nodes), sizeof(num_intermediate_nodes));

            // Read the intermediate nodes
            std::vector<int> intermediate_nodes(num_intermediate_nodes);
            ifs.read(reinterpret_cast<char*>(intermediate_nodes.data()), num_intermediate_nodes * sizeof(int));

            // Store the data
            compressed_paths[start][end] = {intermediate_nodes, total_distance};
        }
    }

    std::cout << "Loaded compressed paths from binary file: " << file_path << std::endl;
    return true;
}