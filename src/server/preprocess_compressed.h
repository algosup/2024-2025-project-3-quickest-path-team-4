#ifndef PREPROCESS_H
#define PREPROCESS_H

#include "graph_data_compressed.h"
#include <unordered_map>

struct are_extremities_singles {
    bool is_start_single = false;
    bool is_end_single = false;
};

void preprocess(graph_data* graph, std::unordered_map<int, int>* single_neighbors);
void check_single_start_or_end(int* start, int* end, std::unordered_map<int, int>* single_neighbors, are_extremities_singles* yes);

#endif // PREPROCESS_H