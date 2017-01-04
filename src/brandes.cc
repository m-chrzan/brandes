#include <fstream>
#include <iostream>

#include "parse.h"
#include "graph.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cerr
            << "USAGE: ./brandes <number-threads> <input-file> <output-file>"
            << std::endl;
        return 1;
    }

    int threads = std::stoi(argv[1]);
    std::string input_file = argv[2];
    std::string output_file = argv[3];

    Parser parser(input_file);

    const Graph &graph = parser.get_graph();

    return 0;
}
