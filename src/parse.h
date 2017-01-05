#ifndef PARSE_H
#define PARSE_H

#include <fstream>
#include <set>
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
    }

    const Graph & get_graph() {
        return graph_;
    }
private:
    Graph graph_;
    std::ifstream input_file_;

    void parse_edge_(std::string edge) {
        int from, to;
        std::stringstream sstream(edge);
        sstream >> from >> to;
        graph_.add_edge(from, to);
    }
};

#endif
