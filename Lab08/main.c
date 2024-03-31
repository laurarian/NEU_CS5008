// Rong Huang
// 03/30/2024
// Compile this assignment with: gcc -Wall main.c -o main

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "my_graph.h"
#include "more_graph.h"

// Tests basic graph operations like node and edge manipulation.
void testGraphFunctionality() {
    printf("Testing basic graph functionality:\n");
    graph_t* g = create_graph();
    assert(g != NULL && "Graph creation failed");

    // Testing adding and removing nodes
    assert(graph_add_node(g, 1) && "Failed to add node 1");
    assert(graph_add_node(g, 2) && "Failed to add node 2");
    assert(!graph_add_node(g, 1) && "Duplicate node 1 added");
    assert(graph_remove_node(g, 2) && "Failed to remove node 2");
    assert(graph_num_nodes(g) == 1 && "Incorrect node count after add/remove");

    // Testing adding and removing edges
    graph_add_node(g, 2); // Re-add node 2 for edge testing
    assert(graph_add_edge(g, 1, 2) && "Failed to add edge 1->2");
    assert(!graph_add_edge(g, 1, 2) && "Duplicate edge 1->2 added");
    assert(graph_remove_edge(g, 1, 2) && "Failed to remove edge 1->2");
    assert(graph_num_edges(g) == 0 && "Incorrect edge count after add/remove");

    // Testing edge existence
    graph_add_edge(g, 1, 2); // Re-add edge for testing
    assert(contains_edge(g, 1, 2) && "Edge 1->2 should exist");
    assert(!contains_edge(g, 2, 1) && "Edge 2->1 should not exist");

    free_graph(g);
    printf("Basic graph functionality tests passed.\n\n");
}

// Tests if a destination node is reachable from a source node within a graph.
void testReachability() {
    printf("Testing graph reachability:\n");
    graph_t* g = create_graph();
    // Setting up a simple graph
    for (int i = 1; i <= 3; i++) {
        graph_add_node(g, i);
    }
    graph_add_edge(g, 1, 2);
    graph_add_edge(g, 2, 3);

    // Testing reachability
    assert(graph_is_reachable(g, 1, 3) && "Node 3 should be reachable from Node 1");
    assert(!graph_is_reachable(g, 3, 1) && "Node 1 should not be reachable from Node 3");

    free_graph(g);
    printf("Graph reachability tests passed.\n\n");
}

// Tests detection of cycles within a graph.
void testCycles() {
    printf("Testing graph cycles:\n");
    graph_t* g = create_graph();
    // Setting up a cyclic graph
    for (int i = 1; i <= 3; i++) {
        graph_add_node(g, i);
    }
    graph_add_edge(g, 1, 2);
    graph_add_edge(g, 2, 3);
    graph_add_edge(g, 3, 1);

    assert(graph_has_cycle(g) && "Graph should have a cycle");

    free_graph(g);
    printf("Graph cycle tests passed.\n\n");
}

// Tests printing of a path from one node to another if such a path exists.
void testPathPrinting() {
    printf("Testing graph path printing:\n");
    graph_t* g = create_graph();
    // Setting up a simple graph
    for (int i = 1; i <= 3; i++) {
        graph_add_node(g, i);
    }
    graph_add_edge(g, 1, 2);
    graph_add_edge(g, 2, 3);

    assert(graph_print_path(g, 1, 3) && "Path from 1 to 3 should exist");

    free_graph(g);
    printf("Graph path printing tests passed.\n\n");
}

int main() {
    testGraphFunctionality();
    testReachability();
    testCycles();
    testPathPrinting();
    printf("All tests passed!\n");
    return 0;
}
