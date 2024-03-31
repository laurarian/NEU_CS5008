// =================== Support Code =================
// Doubly Linked List ( DLL ).
//
//
//
// - Implement each of the functions to create a working DLL.
// - Do not change any of the function declarations
//   - (i.e. dll_t* create_dll() should not have additional arguments)
// - You should not have any 'printf' statements in your DLL functions. 
//   - (You may consider using these printf statements to debug,
//     but they should be removed from your final version)  
//   - (You may write helper functions to help you debug your code such as print_list etc)
// ==================================================
#ifndef MYDLL_H
#define MYDLL_H

#include <stdlib.h> // For malloc.free
// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node {
	void* data;
	struct node* next;
  	struct node* previous;
} node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL {
	int count;	// count keeps track of how many items are in the DLL.
	node_t* head;	// head points to the first node in our DLL.
    	node_t* tail;   // tail points to the last node in our DLL.
} dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t* create_dll(){
    dll_t* myDLL = (dll_t*)malloc(sizeof(dll_t)); // Allocate memory for the DLL
	if(myDLL == NULL) return NULL;// Check for successful allocation
	
	// Initialize DLL fields
	myDLL->count = 0;
	myDLL->head = NULL;
	myDLL->tail = NULL;	
	
	return myDLL;
}

// DLL Empty
// Check if the DLL is empty
// Returns -1 if the dll is NULL.
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t* t) {
    if (t == NULL) return -1; // DLL is NULL
    return (t->count == 0) ? 1 : 0;
}

// push a new item to the front of the DLL ( before the first node in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t* t, void* item){
    // Check if the DLL is NULL
    if (t == NULL) return -1;

    // Allocate memory for a new node and check for failure
    node_t* newNode = (node_t*)malloc(sizeof(node_t)); 
    if (newNode == NULL) return 0; 

    // Set up the new node's data
    newNode->data = item;
    newNode->previous = NULL; 

    // Link the new node with the current head  based on whether the list is empty or not
    if (t->head == NULL) {
        // If the list is empty, new node is both head and tail
        newNode->next = NULL; // No next node
        t->head = newNode;
        t->tail = newNode;
    } else {
        // If the list is not empty, insert the new node before the current head
        newNode->next = t->head; // Point to the old head
        t->head->previous = newNode; // Link the old head back to the new node
        t->head = newNode; // Update the head to the new node
    }

    // Increment the node count
    t->count++;

    return 1;
}

// push a new item to the end of the DLL (after the last node in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* t, void* item){
	// check if the DLL instance is provided
    if (t == NULL) return -1;

    // Allocate memory for a new node and check for failure
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    if (newNode == NULL) return 0;

    // Set up the new node's data
    newNode->data = item;
    newNode->previous = NULL; // Since it will be the new tail

    // Link the new node with the current tail based on whether the list is empty or not
    if (t->tail == NULL) {
        // If the list is empty,new node is both head and tail
        newNode->previous = NULL; //No previous node
        t->head = newNode;
        t->tail = newNode;
    } else {
        // If the list is not empty,insert the new node after the current tail
        t->tail->next = newNode; // Link the old tail forward to the new node
        newNode->previous = t->tail; // Point back to the old tail
        t->tail = newNode;
    }
    
    // Increment the node count
    t->count++;

    return 1;
}

// Returns the first item in the DLL and also removes it from the list.
// Returns -1 if the DLL is NULL. 
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_front(dll_t* t){
	// Check if the DLL is NULL or empty
    if (t == NULL || t->count == 0)
    {
        return NULL; // DLL is NULL or empty
    }


    // Store the first node temporarily
    node_t* temp = t->head;
    void* item = temp->data; //Save the date to return

    // Move head to the next node
    t->head = t->head->next;
    if (t->head != NULL) {
        t->head->previous = NULL; // adjust the new head's previoud pointer
    } else {
        t->tail = NULL; // If the list is empty after removal,set the tail to NULL
    }

    // Free the removed node and decrement the node count
    free(temp);
    t->count--;

	return item; // Return the removed item's data
}

// Returns the last item in the DLL, and also removes it from the list.
// Exits if the DLL is NULL. 
// Returns NULL on failure, i.e., there is nothing to pop from the list.
// Assume no negative numbers in the list or the number zero.
void*  dll_pop_back(dll_t* t){
	// Check if the DLL is NULL or empty
    if (t == NULL || t->count == 0)
    {
        return NULL; // DLL is NULL or empty
    }

    // Store the last node temporarily
    node_t* temp = t->tail;
    void* item = temp->data; // Save the data to return

    // Move tail to the previous node
    t->tail = t->tail->previous;
    if(t->tail != NULL) {
        t->tail->next = NULL; // Adjust the new tail's next pointer
    } else {
        t->head = NULL; // If the list is empty after removal,set the head to NULL
    }
    
    // Free the removed node and decrement the node count
    free(temp);
    t->count--;

	return item; // Return the removed item's data
}

// Inserts a new node before the node at the specified position.
// Returns -1 if the list is NULL
// Returns 1 on success
// Retruns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
int dll_insert(dll_t* t, int pos, void* item){
    // Check if the list is NULL
    if (t == NULL) {
        return -1;
    }

    // Check for invalid position (negative or beyond the size of the list)
    if (pos < 0 || pos > t->count) {
        return 0;
    }

    // Allocate memory for a new node and check success
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    if (newNode == NULL) {
        return 0; // Memory allocation failed
    }

    // Initialize the new node with values
    newNode->data = item;
    newNode->next = NULL;
    newNode->previous = NULL;

    // We need to deal with different cases:
    if (t->count == 0) { // List is empty,the new node becomes both head and tail
        t->head = newNode;
        t->tail = newNode;
    } else if(pos == 0) { // Insert at the beginning of the list
        newNode->next = t->head; // Set the new node's next to the current head of the list
        t->head->previous = newNode; // Set the current head's previous to the new node
        t->head = newNode; // Update the list's head
    } else if(pos == t->count) { // Insert at the end of the list, similar to push_back
        t->tail->next = newNode; // Link the old tail forward to the new node
        newNode->previous = t->tail; // Point back to the old tail
        t->tail = newNode; // Update the list's head
    } else { // Insert somewhere in the middle of the list
        // Find the node currently at the specified position
        node_t* current = t->head;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        // Insert the new node between 'current' and 'current->next'
        newNode->next = current->next;
        newNode->previous = current;
        current->next->previous = newNode;
        current->next = newNode;
    }


    // Increment the count of nodes in the list
    t->count++;
    return 1; 
}

// Returns the item at position pos starting at 0 (0 being the first item)
// Exits if the DLL is NULL
// Returns NULL on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Assume no negative numbers in the list or the number zero.
void* dll_get(dll_t* t, int pos){
    if (t == NULL || pos < 0 || pos >= t->count) {
        return NULL;  // Return NULL if the DLL is NULL or position is out of bounds
    }

    // Use the current pointer to traversal from the head of the list
    node_t* current = t->head; 
    for (int i = 0; i < pos; i++) {
        // Traverse the list to reach the node at the specified position
        current = current->next;
    }

    // Once the desired position is reached, return the data stored in that node
    return current->data;
}

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Exits if the DLL is NULL
// Returns NULL on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Assume no negative numbers in the list or the number zero.
void* dll_remove(dll_t* t, int pos) {
    if (t == NULL || pos < 0 || pos >= t->count) {
        return NULL;  // Return NULL if the DLL is NULL or position is out of bounds
    }

    // Use dll_pop_front if removing the first item
    if (pos == 0) {
        return dll_pop_front(t);
    }

    // Use dll_pop_back if removing the last item
    if (pos == t->count - 1) {
        return dll_pop_back(t);
    }

    // Remove from the middle
    node_t* current = t->head;
    for (int i = 0; i < pos; i++) {
        current = current->next;  // Traverse to the node at the specified position
    }

    // Disconnect the node from the list
    current->previous->next = current->next;
    current->next->previous = current->previous;

    void* item = current->data;  // Save the data to return
    free(current);  // Free the memory of the removed node
    t->count--;  // Decrement the node count

    return item;  // Return the data of the removed node
}

// Helper function
// Removes a specific node from the doubly linked list given a generic pointer.
// Does nothing if the DLL is NULL or the pointer is NULL.
// Assumes that the pointer is part of the list.
// No return value as we are directly removing the node.
void dll_remove_node(dll_t* t, void* ptr) {
    if (t == NULL || ptr == NULL) {
        return; // Do nothing if the list or node is NULL
    }

    node_t* node = (node_t*)ptr;  // Cast the void pointer back to a node_t pointer

    // Handle removal from the head of the list
    if (node == t->head) {
        dll_pop_front(t);
        return;
    }

    // Handle removal from the tail of the list
    if (node == t->tail) {
        dll_pop_back(t);
        return;
    }

    // Disconnect the node from the list for the middle case
    node->previous->next = node->next;
    node->next->previous = node->previous;

    // Free the memory of the removed node
    free(node);

    // Decrement the node count in the list
    t->count--;
}


// Helper function to check if a doubly linked list (DLL) contains a specific node.
// It is used in a graph to check if there is an edge 
// between two nodes. The edge existence is determined by checking if the destination
// node is in the source node's out-neighbors list.
// Returns:
// 1 if the data is found in the list (edge exists),
// 0 otherwise (edge does not exist).
int dll_contains(dll_t* t, void* data) {
    // Check if the list is NULL, return 0 indicating the data is not found
    if (t == NULL) {
        return 0;
    }

    // Start from the head of the list
    node_t* current = t->head;
    while (current != NULL) {
        // Check if the current node's data matches the data we are searching for
        if (current->data == data) {
            return 1; // Data found, return 1
        }
        current = current->next; // Move to the next node in the list
    }
    return 0; // Data not found in the list, return 0
}

// DLL Size
// Exits if the DLL is NULL.
// Returns the current size of a DLL.
int dll_size(dll_t* t) {
    if (t == NULL) {
        fprintf(stderr, "DLL is NULL.\n");
        exit(EXIT_FAILURE);  // Exit the program if the DLL is NULL.
    }
    return t->count;  // Return the count of elements in the DLL.
}


// Free DLL
// Exits if the DLL is NULL.
// Removes a DLL and all of its elements from memory.
// This should be called before the program terminates.
void free_dll(dll_t* t) {
    if (t == NULL) {
        fprintf(stderr, "DLL is NULL.\n");
        exit(EXIT_FAILURE);  // Exit the program if the DLL is NULL.
    }

    // Traverse the list and free each node
    node_t* current = t->head;
    while (current != NULL) {
        node_t* next = current->next;  // Save next node
        free(current);  // Free current node
        current = next;  // Move to next node
    }
    t->head = NULL;
    t->tail = NULL;

    // After freeing all nodes, free the list structure itself
    free(t);
}

#endif
