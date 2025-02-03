#ifndef LOADING_H
#define LOADING_H

#include "graph_data.h"
#include <string>

graph_data load_graph_data(const std::string& file_path);
graph_data load_graph_data_binary(const std::string& file_path);

#endif