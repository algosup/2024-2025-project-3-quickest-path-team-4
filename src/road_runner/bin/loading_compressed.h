#ifndef LOADING_H
#define LOADING_H

#include "graph_data_compressed.h"
#include <string>

graph_data load_graph_data(const std::string& file_path);

#endif // LOADING_H