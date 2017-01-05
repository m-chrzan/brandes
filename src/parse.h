#ifndef PARSE_H
#define PARSE_H

#include <fstream>
#include <sstream>
#include <string>

#include "graph.h"

class Parser {
public:
    Parser(std::string filename) : graph_(), input_file_(filename) {
        std::string edge;
        while (std::getline(input_file_, edge)) {
            parse_edge_(edge);
        }
        graph_.sort_vertices();
    }

    const Graph& get_graph() {
        return graph_;
    }
private:
    Graph graph_;
    std::ifstream input_file_;

    void parse_edge_(std::string edge) {
        std::stringstream sstream(edge);

        int from, to;
        sstream >> from >> to;

        graph_.add_edge(from, to);
    }
};

#endif
