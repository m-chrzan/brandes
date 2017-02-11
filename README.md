# Brandes's Algorithm

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
