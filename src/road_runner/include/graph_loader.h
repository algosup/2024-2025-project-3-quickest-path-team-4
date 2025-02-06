// graph_loader.h
#pragma once
#include "graph_data.h"
#include <string>
#include <optional>

class GraphLoader {
public:
    static std::optional<GraphData> load_from_csv(const std::string& file_path);
    static bool save_to_binary(const GraphData& graph, const std::string& file_path);
    static std::optional<GraphData> load_from_binary(const std::string& file_path);
};