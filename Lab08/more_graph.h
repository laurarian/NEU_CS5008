/*
 * moregraph.h - Extension of basic graph functionality.
 * Provides methods for checking cycles, path printing,
 * and node reachability within graphs.
 * Rong Huang
 * 03/30/2024
 */

#ifndef MOREGRAPH_H
#define MOREGRAPH_H

#include "my_graph.h" 
#include <stdio.h>


// Check if the destination is reachable from the source using BFS.
// Returns 1 if reachable, 0 if not reachable, and -1 if the graph is NULL.
int graph_is_reachable(graph_t *g, int source, int dest) {
    if (g == NULL) return -1; // Graph is NULL

    graph_node_t* srcNode = find_node(g, source);
    graph_node_t* destNode = find_node(g, dest);
    if (srcNode == NULL || destNode == NULL) return 0; // Source or destination node does not exist

    visited_list_t* visited = create_visited_list();
    dll_t* queue = create_dll(); // Use a queue for BFS
    dll_push_back(queue, srcNode);

    while (dll_size(queue) > 0) {
        graph_node_t* currentNode = (graph_node_t*)dll_pop_front(queue);
        if (currentNode == destNode) {
            free_dll(queue);
            free_visited_list(visited);
            return 1; // Destination is reachable
        }

        if (!is_node_visited(visited, currentNode)) {
            add_visited_node(visited, currentNode);
            node_t* adjNode = currentNode->outNeighbors->head;
            while (adjNode != NULL) {
                dll_push_back(queue, ((graph_node_t*)adjNode->data));
                adjNode = adjNode->next;
            }
        }
    }

    free_dll(queue);
    free_visited_list(visited);
    return 0; // Destination is not reachable
}


// Helper function for DFS cycle check. It also avoids revisiting the parent node.
int dfs_has_cycle(graph_t* g, graph_node_t* node, graph_node_t* parent, visited_list_t* visited) {
    add_visited_node(visited, node);

    node_t* adjNode = node->outNeighbors->head;
    while (adjNode != NULL) {
        graph_node_t* adjGraphNode = (graph_node_t*)adjNode->data;
        if (!is_node_visited(visited, adjGraphNode)) {
            if (dfs_has_cycle(g, adjGraphNode, node, visited)) return 1; // Cycle found
        } else if (adjGraphNode != parent) return 1; // Cycle detected
        adjNode = adjNode->next;
    }

    return 0; // No cycle found from this node
}

// Check if there is a cycle in the graph using DFS.
// Returns 1 if a cycle exists, 0 if no cycles exist, and -1 if the graph is NULL.
int graph_has_cycle(graph_t *g) {
    if (g == NULL) return -1; // Graph is NULL

    visited_list_t* visited = create_visited_list();
    node_t* currentNode = g->nodes->head;
    while (currentNode != NULL) {
        graph_node_t* graphNode = (graph_node_t*)currentNode->data;
        if (!is_node_visited(visited, graphNode)) {
            if (dfs_has_cycle(g, graphNode, NULL, visited)) {
                free_visited_list(visited);
                return 1; // Cycle found
            }
        }
        currentNode = currentNode->next;
    }

    free_visited_list(visited);
    return 0; // No cycle in the graph
}


// Helper function for DFS path printing.
int dfs_print_path(graph_t* g, graph_node_t* node, graph_node_t* dest, visited_list_t* visited) {
    if (node == dest) { // Destination reached
        printf("%d ", node->data); // Print destination
        return 1;
    }

    add_visited_node(visited, node);

    node_t* adjNode = node->outNeighbors->head;
    while (adjNode != NULL) {
        graph_node_t* adjGraphNode = (graph_node_t*)adjNode->data;
        if (!is_node_visited(visited, adjGraphNode) && dfs_print_path(g, adjGraphNode, dest, visited)) {
            printf("%d ", node->data); // Print path in reverse order
            return 1;
        }
        adjNode = adjNode->next;
    }

    return 0; // Path does not exist
}


// Prints any path from source to destination if exists using DFS.
// Returns 1 if there is a path, 0 if there is not a path, and -1 if the graph is NULL.
int graph_print_path(graph_t *g, int source, int dest) {
    if (g == NULL) return -1; // Graph is NULL

    graph_node_t* srcNode = find_node(g, source);
    graph_node_t* destNode = find_node(g, dest);
    if (srcNode == NULL || destNode == NULL) return 0; // Source or destination node does not exist

    visited_list_t* visited = create_visited_list();
    if (dfs_print_path(g, srcNode, destNode, visited)) {
        free_visited_list(visited);
        printf("\n"); // New line after the path
        return 1; // Path found and printed
    }

    free_visited_list(visited);
    return 0; // No path found
}
#endif // MOREGRAPH_H
