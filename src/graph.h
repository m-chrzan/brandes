#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>

class Graph {
public:
    Graph() : vertices_(), graph_() {}

    void add_vertex(int vertex) {
        if (vertices_.find(vertex) == vertices_.end()) {
            vertices_.insert(vertex);
            graph_[vertex] = std::vector<int>();
        }
    }

    void add_edge(int from, int to) {
        add_vertex(from);
        add_vertex(to);
        graph_[from].push_back(to);
    }

    const std::set<int> & get_vertices() const {
        return vertices_;
    }

    const std::vector<int> & get_neighbors(int vertex) const {
        return graph_.find(vertex)->second;
    }
private:
    std::set<int> vertices_;
    std::map<int, std::vector<int>> graph_;
};

#endif
