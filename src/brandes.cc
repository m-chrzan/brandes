#include <fstream>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "dependency_calculator.h"
#include "graph.h"
#include "parse.h"

int threads;
std::string input_file;
std::string output_file;

Graph graph;
std::vector<double> betweenness;
std::queue<int> vertices_to_process;

std::vector<std::thread> threads_list;
std::mutex queue_mutex;
std::mutex betweenness_mutex;

void parse_args(int argc, char *argv[]) {
    if (argc < 4) {
        std::cerr
            << "USAGE: ./brandes <number-threads> <input-file> <output-file>"
            << std::endl;
        exit(1);
    }

    threads = std::stoi(argv[1]);
    input_file = argv[2];
    output_file = argv[3];
}

void parse_input() {
    Parser parser(input_file);
    graph = parser.get_graph();
}

void init() {
    for (int vertex = 0; vertex < graph.get_number_vertices(); vertex++) {
        betweenness.push_back(0);
        vertices_to_process.push(vertex);
    }
}

int next_vertex() {
    std::lock_guard<std::mutex> lock(queue_mutex);

    if (vertices_to_process.empty()) {
        return -1;
    }

    int vertex = vertices_to_process.front();
    vertices_to_process.pop();

    return vertex;
}

void update_betweenness(int vertex, DependencyCalculator& dc) {
    std::lock_guard<std::mutex> lock(betweenness_mutex);

    for (int v = 0; v < graph.get_number_vertices(); v++) {
        if (v != vertex ) {
            betweenness[v] += dc.get_dependency(v);
        }
    }
}

void launch_threads() {
    for (int i = 0; i < threads; i++) {
        threads_list.emplace_back([&] () {
            int vertex = next_vertex();
            while(vertex != -1) {
                DependencyCalculator dc(graph, vertex);
                update_betweenness(vertex, dc);

                vertex = next_vertex();
            }
        });
    }
}

void join_threads() {
    for (std::thread& thread : threads_list) {
        thread.join();
    }
}

void print_betweenness() {
    std::ofstream fout(output_file);

    for (int vertex = 0; vertex < graph.get_number_vertices(); vertex++) {
        if (graph.has_out_edges(vertex)) {
            fout << graph.get_real_vertex(vertex) << " "
                 << betweenness[vertex] << std::endl;
        }
    }
}

int main(int argc, char *argv[]) {
    parse_args(argc, argv);
    parse_input();

    init();

    launch_threads();
    join_threads();

    print_betweenness();

    return 0;
}
