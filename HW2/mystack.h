// =================== Support Code =================
// Stack
//
//
//
// - Implement each of the functions to create a working stack.
// - Do not change any of the function declarations
//   - (i.e. stack_t* create_stack() should not have additional arguments)
// - You should not have any 'printf' statements in your stack functions. 
//   - (You may consider using these printf statements to debug, 
//      but they should be removed from your final version)
// ==================================================
#include <stdlib.h> 

#ifndef MYSTACK_H
#define MYSTACK_H

// Stores the maximum 'depth' of our stack.
// Our implementation enforces a maximum depth of our stack.
// (i.e. capacity cannot exceed MAX_DEPTH for any stack)
# define MAX_DEPTH 32

// Create a node data structure to store data within
// our stack. In our case, we will stores 'integers'
typedef struct node{
	int data;
	struct node* next;
}node_t;

// Create a stack data structure
// Our stack holds a single pointer to a node, which
// is a linked list of nodes.
typedef struct stack{
	int count;		// count keeps track of how many items
				// are in the stack.
	unsigned int capacity;	// Stores the maximum size of our stack
	node_t* head;		// head points to a node on the top of our stack.
}stack_t;

// Creates a stack
// Returns a pointer to a newly created stack.
// The stack should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The stacks fields should also be initialized to default values.
stack_t* create_stack(unsigned int capacity){
	// Modify the body of this function as needed.
    // Allocate memory for the stack
    stack_t* myStack = (stack_t*)malloc(sizeof(stack_t));
    myStack->count = 0;
    myStack->capacity = capacity; 
    myStack->head = NULL;// Initially, the stack is empty, so head is NULL
    return myStack;
}

// Stack Empty
// Check if the stack is empty
// Returns 1 if true (The stack is completely empty)
// Returns 0 if false (the stack has at least one element enqueued)
int stack_empty(stack_t* s){
	// Return 1 if empty, 0 otherwise
    if(s->count == 0){
        return 1;
    }
    return 0;
}

// Stack Full
// Check if the stack is full
// Returns 1 if true (The Stack is completely full, i.e. equal to capacity)
// Returns 0 if false (the Stack has more space available to enqueue items)
int stack_full(stack_t* s){
	// Return 1 if full, 0 otherwise
    if(s->count == s->capacity){
        return 1;
    }
    return 0;
}

// Enqueue a new item
// i.e. push a new item into our data structure
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. if the Stack is full that is an error, but does not crash the program).
int stack_enqueue(stack_t* s, int item){
	// check if the stack is full or not, if the stack is full, return -1 
    if (stack_full(s)) {
        return -1;
    }
    //push a new node to the stack(allocate the memory,link the node,increament the size)
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    newNode->data = item;
    newNode->next=s->head;// Link the new node with the current top
    s->head = newNode;// Update the stack's top to the new node
    s->count++; // Increase the stack's item count
    return 0;
}

// Dequeue an item
// Returns the item at the front of the stack and
// removes an item from the stack.
// Removing from an empty stack should crash the program, call exit(1).
int stack_dequeue(stack_t* s){
    //check if the stack is empty,if it's empty,, call exit(1)
	if (stack_empty(s)) {
        exit(1);
    }

	//pop the last node from the stack
    node_t* temp = s->head;// Temporarily store the top node
    int item = temp->data;// Get the data from the top node
    s->head = s->head->next; // Move the head pointer to the next node
    free(temp);//// Free the memory of the removed node
    s->count--; // Decrease the stack's item count
    return item; // Return the removed item's data
}

// Stack Size
// Queries the current size of a stack
// A stack that has not been previously created will crash the program.
// (i.e. A NULL stack cannot return the size)
unsigned int stack_size(stack_t* s){
    // Check if the stack pointer is NULL
	if (s == NULL) {
        exit(1);        
    }
    // If s is not NULL, return the actual size of the stack.
	return s->count;
}

// Free stack
// Removes a stack and ALL of its elements from memory.
// This should be called before the proram terminates.
void free_stack(stack_t* s){
	// if the stack is not null.call the dequeue function to free each node at a time
    while (!stack_empty(s)) {
        stack_dequeue(s); // Remove all nodes from the stack
    }
    free(s); // Free the stack structure itself
}

//stack_peek
//Returns the top value of the stack without removing it.
int stack_peek(stack_t* s) {
    //check if the stack is empty or not,if it's empty,terminate the program.
    if (stack_empty(s)) {
        exit(1); 
    }
    return s->head->data; // Return the top element's data
}

//stack_equal
//Checks if two stacks are equal.
//Returns 1 if the stacks are equal, 0 otherwise.
int stack_equals(stack_t* s1, stack_t* s2) {
    // First check if both stacks are NULL or both have the same count
    if (s1 == s2) return 1; // Same stack or both NULL
    if (s1 == NULL || s2 == NULL) return 0; // One is NULL, not equal
    if (s1->count != s2->count) return 0; // Different sizes, not equal

    node_t* current1 = s1->head;
    node_t* current2 = s2->head;

    // Iterate through both stacks and compare elements
    while (current1 != NULL && current2 != NULL) {
        if (current1->data != current2->data) {
            return 0; // Found a mismatch, stacks are not equal
        }
        current1 = current1->next;
        current2 = current2->next;
    }

    return 1; // All elements matched, stacks are equal
}

#endif
