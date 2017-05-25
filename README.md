# Brandes' Algorithm

A parallel implementation of Brandes' algorithm for calculating [betweenness
centrality](https://en.wikipedia.org/wiki/Betweenness_centrality) in unweighted
graphs.

## Building

    mkdir build
    cd build
    cmake ..
    make

## Running

    ./brandes <number threads> <input file> <output file>

### Graph representation

This implementation expects a simple, directed, unweighted graph with vertices
labeled with integers.

Sample input file:

    0 2
    2 0
    2 3
    2 4
    3 2
    3 5
    3 6

Here each line represents a directed edge from the first node to the second.

The output will contain a line for each node with at least one out edge, of the
form `<node> <BC[node]>`.  Thus for the above sample input, the output file
should contain:

    0 0
    2 6
    3 4

## Links

* [*A Faster Algorithm for Betweenness Centrality*
](https://kops.uni-konstanz.de/bitstream/handle/123456789/5739/algorithm.pdf?sequence=1)
(U. Brandes)

* [*Parallel Algorithms for Evaluating Centrality Indices in Real-World Networks*
](https://smartech.gatech.edu/bitstream/handle/1853/14428/GT-CSE-06-13.pdf)
(D. A. Bader, K. Madduri)
