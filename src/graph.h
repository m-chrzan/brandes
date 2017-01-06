#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Graph {
public:
    Graph() : vertices_(), graph_(), number_vertices_(0) {}

    void add_vertex(int vertex) {
        if (vertices_.find(vertex) == vertices_.end()) {
            vertices_.insert(vertex);
            orderable_vertices_.push_back(vertex);

            graph_.push_back(std::vector<int>());
            has_out_edges_.push_back(false);
            number_vertices_++;
        }
    }

    void add_edge(int from, int to) {
        graph_[mapped_to_[from]].push_back(mapped_to_[to]);
        has_out_edges_[mapped_to_[from]] = true;
    }

    void done_with_vertices() {
        sort_vertices_();
        map_vertices_();
    }

    int get_number_vertices() const {
        return number_vertices_;
    }

    const std::vector<int>& get_neighbors(int vertex) const {
        return graph_[vertex];
    }

    bool has_out_edges(int vertex) const {
        return has_out_edges_[vertex];
    }

    int get_real_vertex(int vertex) const {
        return orderable_vertices_[vertex];
    }
private:
    std::unordered_set<int> vertices_;
    std::vector<int> orderable_vertices_;
    std::vector<std::vector<int>> graph_;
    std::vector<bool> has_out_edges_;
    std::unordered_map<int, int> mapped_to_;
    int number_vertices_;

    void sort_vertices_() {
        std::sort(orderable_vertices_.begin(), orderable_vertices_.end());
    }

    void map_vertices_() {
        for (int i = 0; i < number_vertices_; i++) {
            mapped_to_[orderable_vertices_[i]] = i;
        }
    }
};

#endif
