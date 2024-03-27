// Rong Huang
// 03/26/2024
//
// Compile this assignment with: gcc -Wall main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"

// Unit test function
void test() {
    // Create a new graph
    graph_t* graph = create_graph();
    assert(graph != NULL);
    assert(graph_num_nodes(graph) == 0);
    assert(graph_num_edges(graph) == 0);

    // Add nodes to the graph
    assert(graph_add_node(graph, 1) == 1);
    assert(graph_add_node(graph, 2) == 1);
    assert(graph_add_node(graph, 1) == 0); // Attempt to add duplicate node
    assert(graph_num_nodes(graph) == 2);

    // Add edges to the graph
    assert(graph_add_edge(graph, 1, 2) == 1);
    assert(graph_add_edge(graph, 1, 3) == 0); // Node 3 doesn't exist
    assert(graph_add_edge(graph, 1, 2) == 0); // Duplicate edge
    assert(graph_num_edges(graph) == 1);

    // Test neighbors
    dll_t* outNeighbors = getOutNeighbors(graph, 1);
    assert(dll_size(outNeighbors) == 1);
    dll_t* inNeighbors = getInNeighbors(graph, 2);
    assert(dll_size(inNeighbors) == 1);

    // Remove edges
    assert(graph_remove_edge(graph, 1, 2) == 1);
    assert(graph_remove_edge(graph, 1, 2) == 0); // Edge already removed
    assert(graph_num_edges(graph) == 0);

    // Remove nodes
    assert(graph_remove_node(graph, 1) == 1);
    assert(graph_remove_node(graph, 1) == 0); // Node already removed
    assert(graph_num_nodes(graph) == 1);

    // Free graph
    free_graph(graph);
    printf("All tests passed.\n");
}


// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

int main(int argc, const char * argv[]) {

    graph_t * graph = create_graph();

    graph_add_node(graph, 1);
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);

    printf("total nodes: 2==%d\n", graph_num_nodes(graph));

    // Call the test function
    test();

    return 0;
}
