// =================== Support Code =================
// Graph.
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they 
//      should be removed from your final version)
// ==================================================
#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h"
#include <stdlib.h>
#include <assert.h>
// Create a graph data structure
typedef struct graph{
    int numNodes;
    int numEdges;
    dll_t* nodes;     //an array of nodes storing all of our nodes.
} graph_t;

typedef struct graph_node{
    int data;
    dll_t* inNeighbors;
    dll_t* outNeighbors;
} graph_node_t;

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
// Returns NULL if we cannot allocate memory.
graph_t* create_graph(){
    // Modify the body of this function as needed.
    graph_t* myGraph= malloc(sizeof(graph_t));
    myGraph->nodes = create_dll();
    myGraph->numEdges = 0;
    myGraph->numNodes = 0;
    return myGraph;
}

// =================== Visited Nodes List ===================
typedef struct {
    dll_t* visitedNodes;  // DLL to store visited nodes
} visited_list_t;

// Initialize the visited nodes list
visited_list_t* create_visited_list() {
    visited_list_t* visitedList = (visited_list_t*)malloc(sizeof(visited_list_t));
    if (visitedList == NULL) {
        return NULL;  // Memory allocation failed
    }

    visitedList->visitedNodes = create_dll();
    if (visitedList->visitedNodes == NULL) {
        free(visitedList);
        return NULL;  // Memory allocation failed
    }

    return visitedList;
}

// Add a node to the visited list
void add_visited_node(visited_list_t* visitedList, graph_node_t* node) {
    if (visitedList == NULL || visitedList->visitedNodes == NULL || node == NULL) {
        return;
    }

    // Check if the node is already in the visited list
    node_t* current = visitedList->visitedNodes->head;
    while (current != NULL) {
        if (current->data == node) {
            return;  // Node already visited
        }
        current = current->next;
    }

    // Add the node to the visited list
    dll_push_back(visitedList->visitedNodes, node);
}

// Check if a node has been visited
int is_node_visited(visited_list_t* visitedList, graph_node_t* node) {
    if (visitedList == NULL || visitedList->visitedNodes == NULL || node == NULL) {
        return 0;  // Visited list not initialized
    }

    // Check if the node is in the visited list
    node_t* current = visitedList->visitedNodes->head;
    while (current != NULL) {
        if (current->data == node) {
            return 1;  // Node is visited
        }
        current = current->next;
    }

    return 0;  // Node is not visited
}

// Free the visited list and its contents
void free_visited_list(visited_list_t* visitedList) {
    if (visitedList == NULL) {
        return;
    }

    // Assuming dll_free() is a function to free the DLL and its nodes' data
    free_dll(visitedList->visitedNodes);
    free(visitedList);
}

// ======================================
// Returns the node pointer if the node exists.
// Returns NULL if the node doesn't exist or the graph is NULL
graph_node_t* find_node(graph_t* g, int value) {
    if (g == NULL || g->nodes == NULL) return NULL; // Check for valid graph

    // Iterate over the list of nodes in the graph
    node_t* current = g->nodes->head;
    while (current != NULL) {
        graph_node_t* node = (graph_node_t*)current->data;
        if (node->data == value) {
            return node; // Node found
        }
        current = current->next;
    }
    return NULL; // Node not found
}

// Creates a graph node
// Note: This relies on your dll implementation.
graph_node_t * create_graph_node(int value){
    graph_node_t * graph_node = malloc(sizeof(graph_node_t));
    
    if ( graph_node == NULL ) return NULL;
    
    graph_node->data = value;
    graph_node->inNeighbors = create_dll();
    graph_node->outNeighbors = create_dll();
    
    return graph_node;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node already exists )
// Returns -1 if the graph is NULL.
int graph_add_node(graph_t* g, int value){
    if ( g == NULL ) return -1;
    
    if (find_node(g, value) != NULL) return -1;
    
    graph_node_t * newNode = create_graph_node(value);
    if ( newNode == NULL ) return -1;
    
    assert(g->nodes);
    dll_push_back(g->nodes, newNode);
    g->numNodes++;
    
    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node doesn't exist )
// Returns -1 if the graph is NULL.
int graph_remove_node(graph_t* g, int value){
    // TODO: Implement me!
    // The function removes the node from the graph along with any edges associated with it.
    // That is, this node would have to be removed from all the in and out neighbor's lists that countain it.
    if (g == NULL) return -1;  // Check for valid graph

    graph_node_t* nodeToRemove = find_node(g, value);
    if (nodeToRemove == NULL) return 0;  // Node not found

    // Remove all edges associated with this node
    while (!dll_empty(nodeToRemove->inNeighbors)) {
        graph_node_t* neighbor = (graph_node_t*)dll_pop_front(nodeToRemove->inNeighbors);
        dll_remove_node(neighbor->outNeighbors, nodeToRemove);
    }
    while (!dll_empty(nodeToRemove->outNeighbors)) {
        graph_node_t* neighbor = (graph_node_t*)dll_pop_front(nodeToRemove->outNeighbors);
        dll_remove_node(neighbor->inNeighbors, nodeToRemove);
    }

    // Remove the node from the graph's list of nodes
    node_t* current = g->nodes->head;
    while (current != NULL) {
        if (current->data == nodeToRemove) {
            dll_remove_node(g->nodes, current);
            break;
        }
        current = current->next;
    }

    free(nodeToRemove->inNeighbors);
    free(nodeToRemove->outNeighbors);
    free(nodeToRemove);

    g->numNodes--;
    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge already exists )
// Returns -1 if the graph is NULL.
int graph_add_edge(graph_t * g, int source, int destination){
    // TODO: Implement me!
    // The function adds an edge from source to destination but not the other way.
    // Make sure you are not adding the same edge multiple times.
    // Make sure you modify the in and out neighbors appropriatelly. destination will be an out neighbor of source.
    // Source will be an in neighbor of destination.
    if (g == NULL) return -1;

    graph_node_t* srcNode = find_node(g, source);
    graph_node_t* destNode = find_node(g, destination);

    if (srcNode == NULL || destNode == NULL) return -1;

    // Check if the edge already exists
    if (dll_contains(srcNode->outNeighbors, destNode)) {
        return 0; // Edge already exists
    }

    dll_push_back(srcNode->outNeighbors, destNode);
    dll_push_back(destNode->inNeighbors, srcNode);
    g->numEdges++;

    return 1;
  
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge doesn't exists )
// Returns -1 if the graph is NULL.
int graph_remove_edge(graph_t * g, int source, int destination){
    // TODO: Implement me!
    //The function removes an edge from source to destination but not the other way.
    //Make sure you remove destination from the out neighbors of source.
    //Make sure you remove source from the in neighbors of destination.
    if (g == NULL) return -1;  // Check if the graph is valid.

    graph_node_t* srcNode = find_node(g, source);
    graph_node_t* destNode = find_node(g, destination);

    if (srcNode == NULL || destNode == NULL) return 0;  // Check if both nodes exist in the graph.

    // Here we check if an edge actually exists between source and destination
    if (!dll_contains(srcNode->outNeighbors, destNode)) {
        return 0;  // Edge does not exist, so removal is not possible.
    }

    // If the edge exists, we proceed to remove it
    // Remove the edge from the source node's outNeighbors
    for (node_t* current = srcNode->outNeighbors->head; current != NULL;) {
        node_t* next = current->next;  // Save the next node before potentially removing the current node
        if (current->data == destNode) {
            dll_remove_node(srcNode->outNeighbors, current);
            break;  // Exit the loop immediately after removing the node
        }
        current = next;  // Move to the next node
    }

    // Remove the edge from the destination node's inNeighbors
    for (node_t* current = destNode->inNeighbors->head; current != NULL;) {
        node_t* next = current->next;  // Save the next node before potentially removing the current node
        if (current->data == srcNode) {
            dll_remove_node(destNode->inNeighbors, current);
            break;  // Exit the loop immediately after removing the node
        }
        current = next;  // Move to the next node
    }

    g->numEdges--;  // Decrement the count of edges in the graph.
    return 1;

}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist )
// Returns -1 if the graph is NULL.
int contains_edge( graph_t * g, int source, int destintaion){
    // TODO: Implement me!
    if (g == NULL) return -1;

    graph_node_t* srcNode = find_node(g, source);
    graph_node_t* destNode = find_node(g, destintaion);

    if (srcNode == NULL || destNode == NULL) return -1;

    return dll_contains(srcNode->outNeighbors, destNode);

}

// Returns dll_t* of all the in neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getInNeighbors( graph_t * g, int value ){
    // TODO: Implement me!
    graph_node_t* node = find_node(g, value);
    if (node == NULL) return NULL;

    return node->inNeighbors;

}

// Returns the number of in neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumInNeighbors( graph_t * g, int value){
    // TODO: Implement me!
    dll_t* neighbors = getInNeighbors(g, value);
    return neighbors ? dll_size(neighbors) : -1;

}

// Returns dll_t* of all the out neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getOutNeighbors( graph_t * g, int value ){
    // TODO: Implement me!
    graph_node_t* node = find_node(g, value);
    if (node == NULL) return NULL;

    return node->outNeighbors;

}

// Returns the number of out neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumOutNeighbors( graph_t * g, int value){
    // TODO: Implement me!
    dll_t* neighbors = getOutNeighbors(g, value);
    return neighbors ? dll_size(neighbors) : -1;
}

// Returns the number of nodes in the graph
// Returns -1 if the graph is NULL.
int graph_num_nodes(graph_t* g){
    // TODO: Implement me!
    if (g == NULL) return -1;
    return g->numNodes;
}

// Returns the number of edges in the graph,
// Returns -1 on if the graph is NULL
int graph_num_edges(graph_t* g){
    // TODO: Implement me!
    if (g == NULL) return -1;
    return g->numEdges;
}

// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the program terminates.
// Make sure you free all the dll's too.
void free_graph(graph_t* g){
    // TODO: Implement me!
    if (g == NULL)
        return;

    // Free each node and its neighbors
    node_t *current = g->nodes->head;
    while (current != NULL)
    {
        graph_node_t *node = (graph_node_t *)current->data;
        free_dll(node->inNeighbors);
        free_dll(node->outNeighbors);
        free(node);
        current = current->next;
    }

    // Free the list of nodes
    free_dll(g->nodes);

    // Free the graph itself
    free(g);
}

#endif
