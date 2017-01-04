#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>

class Graph {
public:
    Graph() : graph_() {}

    void add_vertex(int vertex) {
        graph_[vertex] = std::vector<int>();
    }

    void add_edge(int from, int to) {
        graph_[from].push_back(to);
    }

    std::set<int> get_vertices() {
        std::set<int> vertices;

        for (auto vertex : graph_) {
            vertices.insert(vertex.first);
        }

        return vertices;
    }


    std::vector<int> const& get_neighbors(int vertex) {
        return graph_[vertex];
    }
private:
    std::map<int, std::vector<int>> graph_;
};

#endif
