#ifndef GRAPH_DATA_H
#define GRAPH_DATA_H

#include <vector>
#include <map>
#include <string>
#include <optional>

class GraphData {
private:
    std::vector<std::map<int, int>> adjacency_;
    size_t edge_count_ = 0;

public:
    size_t size() const { return adjacency_.size(); }
    size_t get_edge_count() const { return edge_count_; }
    
    void add_edge(int from, int to, int weight) {
        if (from >= adjacency_.size()) adjacency_.resize(from + 1);
        if (to >= adjacency_.size()) adjacency_.resize(to + 1);
        adjacency_[from][to] = weight;
        adjacency_[to][from] = weight;
        edge_count_ += 2;
    }
    
    const std::map<int, int>& get_neighbors(int vertex) const {
        return adjacency_[vertex];
    }
    
    friend class GraphLoader;
};

// Function declarations after class definition
GraphData load_graph_data_binary(const std::string& file_path);
std::optional<GraphData> load_from_csv(const std::string& file_path);

#endif // GRAPH_DATA_H