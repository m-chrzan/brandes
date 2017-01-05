#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Graph {
public:
    Graph() : vertices_(), graph_() {}

    void add_vertex(int vertex) {
        if (vertices_.find(vertex) == vertices_.end()) {
            vertices_.insert(vertex);
            orderable_vertices_.push_back(vertex);
            graph_[vertex] = std::vector<int>();
        }
    }

    void add_edge(int from, int to) {
        add_vertex(from);
        add_vertex(to);
        graph_[from].push_back(to);
        has_out_edges_.insert(from);
    }

    void sort_vertices() {
        std::sort(orderable_vertices_.begin(), orderable_vertices_.end());
    }

    const std::vector<int> & get_vertices() const {
        return orderable_vertices_;
    }

    const std::vector<int> & get_neighbors(int vertex) const {
        return graph_.find(vertex)->second;
    }

    bool has_out_edges(int vertex) const {
        return has_out_edges_.count(vertex) > 0;
    }

private:
    std::unordered_set<int> vertices_;
    std::vector<int> orderable_vertices_;
    std::unordered_map<int, std::vector<int>> graph_;
    std::unordered_set<int> has_out_edges_;
};

#endif
