#ifndef GRAPH_DATA_H
#define GRAPH_DATA_H

#include <vector>
#include <map>

class GraphData {
private:
    std::vector<std::map<int, int>> adjacency_;

public:
    size_t size() const { return adjacency_.size(); }
    
    void process_edge(GraphData& g, int node, int neighbor, int weight) {
    g.add_edge(node, neighbor, weight);
    }

    void add_edge(int from, int to, int weight) {
        if (from >= adjacency_.size()) adjacency_.resize(from + 1);
        if (to >= adjacency_.size()) adjacency_.resize(to + 1);
        adjacency_[from][to] = weight;
        adjacency_[to][from] = weight;
    }
    
    const std::map<int, int>& get_neighbors(int vertex) const {
        return adjacency_[vertex];
    }
    friend class GraphLoader;
    friend class Loader;  // For binary file loading
};


#endif // GRAPH_DATA_H