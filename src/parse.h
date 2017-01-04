#ifndef PARSE_H
#define PARSE_H

#include <fstream>
#include <set>
#include "graph.h"

class Parser {
public:
    Parser(std::string filename) : graph_(), input_file_(filename) {
        parse_number_edges_();

        for (int i = 0; i < number_edges_; i++) {
            parse_edge_();
        }
    }

    const Graph & get_graph() {
        return graph_;
    }
private:
    Graph graph_;
    std::ifstream input_file_;
    int number_edges_;

    void parse_number_edges_() {
        input_file_ >> number_edges_;
    }

    void parse_edge_() {
        int from, to;

        input_file_ >> from >> to;

        graph_.add_edge(from, to);
    }
};

#endif
