#ifndef PARSE_H
#define PARSE_H

#include <fstream>
#include <sstream>
#include <string>

#include "graph.h"

class Parser {
public:
    Parser(std::string filename) : graph_(), input_file_(filename) {
        read_file_();
        add_vertices_();
        add_edges_();
    }

    const Graph& get_graph() {
        return graph_;
    }
private:
    Graph graph_;
    std::ifstream input_file_;
    std::vector<std::pair<int, int>> edges_;

    void read_file_() {
        std::string edge;
        while (std::getline(input_file_, edge)) {
            parse_edge_(edge);
        }
    }

    void parse_edge_(std::string edge) {
        std::stringstream sstream(edge);

        int from, to;
        sstream >> from >> to;

        edges_.push_back(std::pair<int, int>(from, to));
    }

    void add_vertices_() {
        for (auto edge : edges_) {
            graph_.add_vertex(edge.first);
            graph_.add_vertex(edge.second);
        }

        graph_.done_with_vertices();
    }

    void add_edges_() {
        for (auto edge : edges_) {
            graph_.add_edge(edge.first, edge.second);
        }
    }
};

#endif
