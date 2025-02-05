#ifndef SAVE_LOAD_BINARY_H
#define SAVE_LOAD_BINARY_H

#include <vector>
#include <unordered_map>  // Add this line
#include <string>         // Add this line

// Define the path_info structure
struct path_info {
    std::vector<int> intermediate_nodes;
    int total_distance;
};

// Declare the save and load functions
void save_compressed_paths_binary(const std::string& file_path, const std::unordered_map<int, std::unordered_map<int, path_info>>& compressed_paths);
bool load_compressed_paths_binary(const std::string& file_path, std::unordered_map<int, std::unordered_map<int, path_info>>& compressed_paths);

#endif // SAVE_LOAD_BINARY_H