#ifndef DEPENDENCY_CALCULATOR_H
#define DEPENDENCY_CALCULATOR_H

#include <stack>
#include <queue>
#include <vector>
#include <unordered_map>

#include "graph.h"

class DependencyCalculator {
public:
    DependencyCalculator(const Graph &graph, int vertex) : graph_(graph),
            vertex_(vertex) {
        init_();
        find_shortest_paths_();
        calculate_dependencies_();
    }

    double get_dependency(int vertex) const {
        return dependency_.find(vertex)->second;
    }
private:
    const Graph &graph_; // (V, E)
    int vertex_; // s
    std::stack<int> stack_; // S
    std::unordered_map<int, std::vector<int>> shortest_path_predecessors_; // P
    std::unordered_map<int, int> shortest_paths_; // sigma
    std::unordered_map<int, int> distance_; // d
    std::queue<int> queue_; // Q
    std::unordered_map<int, double> dependency_; // delta

    void init_() {
        for (int vertex : graph_.get_vertices()) {
            shortest_path_predecessors_[vertex] = std::vector<int>();
            shortest_paths_[vertex] = 0;
            distance_[vertex] = -1;
            dependency_[vertex] = 0;
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
