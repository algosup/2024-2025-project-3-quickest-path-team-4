#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include "binary_writer.h"
#include <string>

bool parse_csv(const std::string& file_path, GraphData& graph_data);

#endif // CSV_PARSER_H