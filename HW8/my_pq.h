// =================== Support Code =================
// Priority Queue (PQ) for Dijkstra's Algorithm.
//
// - Implements a priority queue that stores graph_node_t* along with associated costs.
// - Dequeues the graph_node_t with the minimum cost using linear search.
// ==================================================

#ifndef MYPQ_H
#define MYPQ_H

#include "my_graph.h"
#include <stdio.h>
#include <stdlib.h>

// Define a structure to hold the graph node along with its cost
typedef struct pq_node {
    graph_node_t* node;
    int cost;   // This will store the cost associated with the node
} pq_node_t;

// Priority Queue structure
typedef struct {
    pq_node_t* elements;    // Array of pq_node, which includes graph_node_t* and cost
    int size;               // Current size of the priority queue
    int capacity;           // Capacity of the priority queue
} pq_t;

pq_t* create_pq(int capacity);                  
void pq_insert(pq_t* pq, graph_node_t* node, int cost); 
graph_node_t* pq_remove_min(pq_t* pq);          
int pq_is_empty(pq_t* pq);                      
void free_pq(pq_t* pq); 

// Create a Priority Queue with initial capacity
pq_t* create_pq(int capacity) {
    pq_t* pq = (pq_t*)malloc(sizeof(pq_t));
    pq->elements = (pq_node_t*)malloc(sizeof(pq_node_t) * capacity);
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}                     

void pq_insert(pq_t* pq, graph_node_t* node, int cost) {
    // Check if the node already exists in the queue
    for (int i = 0; i < pq->size; ++i) {
        if (pq->elements[i].node == node) {
            // If the new cost is lower, update the node's cost
            if (pq->elements[i].cost > cost) {
                pq->elements[i].cost = cost;
            }
            // No need to insert the node again, so return
            return;
        }
    }

    // If the node does not exist, then insert it
    if (pq->size >= pq->capacity) {
        pq->capacity *= 2; // Increase the capacity if needed
        pq->elements = (pq_node_t*)realloc(pq->elements, sizeof(pq_node_t) * pq->capacity);
    }

    // Add the new node at the end of the queue
    pq->elements[pq->size].node = node;
    pq->elements[pq->size].cost = cost;
    pq->size++;
}

// Find and remove the node with the smallest cost
graph_node_t* pq_remove_min(pq_t* pq) {
    if (pq->size == 0) {
        return NULL;
    }

    int min_index = 0;
    for (int i = 1; i < pq->size; i++) {
        if (pq->elements[i].cost < pq->elements[min_index].cost) {
            min_index = i;
        }
    }
    graph_node_t* min_node = pq->elements[min_index].node;

    // Remove the found minimum node by replacing it with the last node
    pq->elements[min_index] = pq->elements[--pq->size];
    return min_node;
}

// Check if the priority queue is empty
int pq_is_empty(pq_t* pq) {
    return pq->size == 0;
}

// Free the priority queue resources
void free_pq(pq_t* pq) {
    if (pq) {
        if (pq->elements) {
            free(pq->elements);
        }
        free(pq);
    }
}

#endif // MYPQ_H
