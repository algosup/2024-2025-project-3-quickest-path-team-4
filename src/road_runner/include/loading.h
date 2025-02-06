#ifndef LOADING_H
#define LOADING_H

#include <string>
#include "graph_data.h"

GraphData load_graph_data(const std::string& file_path);
GraphData load_graph_data_binary(const std::string& file_path);

#endif // LOADING_H
