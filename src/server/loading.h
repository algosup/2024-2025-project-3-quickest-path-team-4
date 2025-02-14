#ifndef LOADING_H
#define LOADING_H

#include "graphData.h"
#include <string>

GraphData load_graph_data_from_binary(const std::string& binary_file_path, const std::string& csv_file_path);

#endif // LOADING_H