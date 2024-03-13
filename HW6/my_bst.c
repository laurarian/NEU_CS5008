// Rong Huang
// 03/12/2024
// CS5008 HW6
// Include our header file for our my_bst.c
#include "my_bst.h"

// Include any other libraries needed
#include <stdio.h>
#include <stdlib.h>

// Creates a BST
// Returns a pointer to a newly created BST.
// The BST should be initialized with data on the heap.
// The BST fields should also be initialized to default values(i.e. size=0).
bst_t* bst_create(){
    // Modify the body of this function as needed.
    bst_t* myBST = malloc(sizeof(bst_t)); // Allocate memory for the BST
    if (myBST == NULL) { // Check for memory allocation failure
        return NULL;
    }
    myBST->size = 0; 
    myBST->root = NULL; 
    return myBST;
}

// BST Empty
// Check if the BST is empty
// Returns 1 if true (The BST is completely empty)
// Returns 0 if false (the BST has at least one element)
int bst_empty(bst_t* t){
    // If the BST is NULL or its size is 0, it's empty
    if (t == NULL || t->size == 0) { 
        return 1;
    }
    return 0;
}

// Adds a new node containg item to the BST
// The item is added in the correct position in the BST.
//  - If the data is less than or equal to the current node we traverse left
//  - otherwise we traverse right.
// The bst_function returns '1' upon success
//  - bst_add should increment the 'size' of our BST.
// Returns a -1 if the operation fails.
//      (i.e. the memory allocation for a new node failed).
// Your implementation should should run in O(log(n)) time.
//  - A recursive imlementation is suggested.
// Helper function for bst_add to recursively find the correct spot to insert a new node
// and insert the new node into the BST.
// Returns a pointer to the new node if the insertion is successful, or NULL if a memory
// allocation failure occurs.

// bst_add_helper is a recursive function that inserts a new item into the BST.
// It returns the new root of the subtree after the insertion.
// Parameters:
//   n: the current node (root of the current subtree)
//   item: the item to insert
bstnode_t* bst_add_helper(bstnode_t* n, int item) {
    // If the current node is NULL, create a new node with the item.
    if (n == NULL) {
        bstnode_t* newNode = malloc(sizeof(bstnode_t));
        if (newNode == NULL) {
            // If memory allocation fails, return NULL.
            return NULL;
        }
        // Initialize the new node.
        newNode->data = item;
        newNode->leftChild = NULL;
        newNode->rightChild = NULL;
        return newNode; // Return the new node as the root of this subtree.
    }

    // Determine whether to insert the item in the left or right subtree.
    if (item <= n->data) {
        // Insert in the left subtree.
        n->leftChild = bst_add_helper(n->leftChild, item);
    } else {
        // Insert in the right subtree.
        n->rightChild = bst_add_helper(n->rightChild, item);
    }
    return n; // Return the current node as the root of this subtree.
}

int bst_add(bst_t* t, int item) {
    if (t == NULL) {
        // If the BST pointer is NULL, return -1.
        return -1;
    }
    // Use bst_add_helper to insert the item and update the root of the BST.
    t->root = bst_add_helper(t->root, item);
    if (t->root == NULL) {
        // If the new root is NULL, the memory allocation failed, return -1.
        return -1;
    }
    t->size++; // Increment the size of the BST.
    return 1; // Return success.
}


// Prints the tree in ascending order if order = 0, otherwise prints in descending order.
// A BST that is NULL should print "(NULL)"
// It should run in O(n) time.
void bst_print_helper(bstnode_t* node, int order) {
    if (node == NULL) {
        return; // Base case: node is NULL.
    }
    // Traverse and print the BST in the specified order.
    if (order == 0) {
        // Ascending order: left, node, right
        bst_print_helper(node->leftChild, order);
        printf("%d ", node->data);
        bst_print_helper(node->rightChild, order);
    } else {
        // Descending order: right, node, left
        bst_print_helper(node->rightChild, order);
        printf("%d ", node->data);
        bst_print_helper(node->leftChild, order);
    }
}

void bst_print(bst_t *t, int order) {
    if (t == NULL || t->root == NULL) {
        printf("(NULL)\n");
        return;
    }
    bst_print_helper(t->root, order);
    printf("\n"); // Print newline after printing all elements.
}

// Returns the sum of all the nodes in the bst. 
// A BST that is NULL exits the program.
// It should run in O(n) time.
// Calculates the sum of all nodes in the BST.
int bst_sum_helper(bstnode_t* node) {
    if (node == NULL) {
        return 0; // Base case: node is NULL.
    }
    // Sum this node's data with the sum of left and right subtrees.
    return node->data + bst_sum_helper(node->leftChild) + bst_sum_helper(node->rightChild);
}

int bst_sum(bst_t *t) {
    if (t == NULL || t->root == NULL) {
        printf("Error: BST is NULL.\n");
        exit(EXIT_FAILURE); // Exiting program for NULL BST as per requirement.
    }
    return bst_sum_helper(t->root);
}

// Returns 1 if value is found in the tree, 0 otherwise. 
// For NULL tree -- exit the program. 
// It should run in O(log(n)) time.
// Searches for a value in the BST. Returns 1 if found, 0 otherwise.
int bst_find_helper(bstnode_t* node, int value) {
    if (node == NULL) {
        return 0; // Base case: node is NULL, value not found.
    }
    if (value == node->data) {
        return 1; // Value found.
    } else if (value < node->data) {
        return bst_find_helper(node->leftChild, value); // Search left subtree.
    } else {
        return bst_find_helper(node->rightChild, value); // Search right subtree.
    }
    return 0;
}


int bst_find(bst_t *t, int value) {
    bstnode_t* tem = t->root;

    if (t != NULL) {
        // Use the helper function to search for the value starting from the root.
        int res = bst_find_helper(t->root, value);
        t->root = tem;
        return res;
    } else {
        // If the BST pointer is NULL, exit the program.
        exit(1);
    }
}


// Returns the size of the BST
// A BST that is NULL exits the program.
// (i.e. A NULL BST cannot return the size)
unsigned int bst_size(bst_t* t) {
    if (t != NULL) {
        return t->size;
    } else {
        exit(1);
    }
}

// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the proram terminates.

// Helper function to recursively free nodes in the BST
void bst_free_nodes(bstnode_t* node) {
    if (node == NULL) {
        return; // Base case: node is NULL.
    }
    // Recursively free left and right subtrees before freeing this node.
    bst_free_nodes(node->leftChild);
    bst_free_nodes(node->rightChild);
    free(node); // Free the memory allocated for the current node.
}

// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the program terminates.
void bst_free(bst_t* t) {
    if (t == NULL) {
        return; // Nothing to free if the BST structure itself is NULL.
    }
    bst_free_nodes(t->root); // Free all nodes starting from the root.
    free(t); // Finally, free the BST structure itself.
}

