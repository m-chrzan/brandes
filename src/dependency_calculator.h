#ifndef DEPENDENCY_CALCULATOR_H
#define DEPENDENCY_CALCULATOR_H

#include <queue>
#include <stack>
#include <vector>

#include "graph.h"

class DependencyCalculator {
public:
    DependencyCalculator(const Graph& graph, int vertex) : graph_(graph),
            vertex_(vertex) {
        init_();
        find_shortest_paths_();
        calculate_dependencies_();
    }

    double get_dependency(int vertex) const {
        return dependency_[vertex];
    }
private:
    const Graph& graph_; // (V, E)
    int vertex_; // s

    std::stack<int> stack_; // S
    std::vector<std::vector<int>> shortest_path_predecessors_; // P
    std::vector<int> shortest_paths_; // sigma
    std::vector<int> distance_; // d
    std::queue<int> queue_; // Q
    std::vector<double> dependency_; // delta

    void init_() {
        for (int vertex = 0; vertex < graph_.get_number_vertices(); vertex++) {
            shortest_path_predecessors_.emplace_back();
            shortest_paths_.push_back(0);
            distance_.push_back(-1);
            dependency_.push_back(0);
        }

        shortest_paths_[vertex_] = 1;
        distance_[vertex_] = 0;
        queue_.push(vertex_);
    }

    void find_shortest_paths_() {
        while (!queue_.empty()) {
            int vertex = queue_.front();
            queue_.pop();
            stack_.push(vertex);

            for (int neighbor : graph_.get_neighbors(vertex)) {
                if (distance_[neighbor] < 0) {
                    queue_.push(neighbor);
                    distance_[neighbor] = distance_[vertex] + 1;
                }

                if (distance_[neighbor] == distance_[vertex] + 1) {
                    shortest_paths_[neighbor] += shortest_paths_[vertex];
                    shortest_path_predecessors_[neighbor].push_back(vertex);
                }
            }
        }
    }

    void calculate_dependencies_() {
        while (!stack_.empty()) {
            int vertex = stack_.top();
            stack_.pop();

            for (int predecessor : shortest_path_predecessors_[vertex]) {
                double shortest_path_ratio =
                    (double) shortest_paths_[predecessor] /
                    (double) shortest_paths_[vertex];
                dependency_[predecessor] +=
                    shortest_path_ratio * (1 + dependency_[vertex]);
            }
        }
    }
};

#endif
