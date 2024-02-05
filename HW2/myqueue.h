// =================== Support Code =================
// Queue
//
//
//
// - Implement each of the functions to create a working circular queue.
// - Do not change any of the function declarations
//   - (i.e. queue_t* create_queue(unsigned int _capacity) should not have additional arguments)
// - You should not have any 'printf' statements in your queue functions. 
//   - (You may consider using these printf statements to debug, 
//     but they should be removed from your final version)
// ==================================================
#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <stdlib.h>

// The main data structure for the queue
struct queue{
	unsigned int back;	    // The next free position in the queue
				    		// (i.e. the end or tail of the line)
	unsigned int front;	    // Current 'head' of the queue
				    		// (i.e. the front or head of the line)
	unsigned int size;	    // How many total elements we currently have enqueued.
	unsigned int capacity;  // Maximum number of items the queue can hold
	int* data; 		    	// The 'integer' data our queue holds	
};
// Creates a global definition of 'queue_t' so we 
// do not have to retype 'struct queue' everywhere.
typedef struct queue queue_t;

// Create a queue
// Returns a pointer to a newly created queue.
// The queue should be initialized with data on
// the heap.
queue_t* create_queue(unsigned int _capacity){
    // Allocate memory for the queue structure
    queue_t* myQueue = (queue_t*)malloc(sizeof(queue_t));
    //Initialize the queue
    myQueue->size = 0; 
    myQueue->front = 0;
    myQueue->back = 0; 
    myQueue->capacity = _capacity; 
    // Allocate memory for the queue's data array
    myQueue->data = (int*)malloc(sizeof(int) * _capacity); 

	return myQueue;
}

// Queue Empty
// Check if the queue is empty
// Returns 1 if true (The queue is completely empty)
// Returns 0 if false (the queue has at least one element enqueued)
int queue_empty(queue_t* q){
	if(q->size == 0){
        return 1;
    }
	return 0;
}

// Queue Full
// Check if the queue is Full
// Returns 1 if true (The queue is completely full)
// Returns 0 if false (the queue has more space available to enqueue items)
int queue_full(queue_t* q){
	if(q -> size == q -> capacity) {
        return 1;
    }
	return 0;
}

// Enqueue a new item
// i.e. push a new item into our data structure
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. if the queue is full that is an error).
int queue_enqueue(queue_t* q, int item) {
    if (queue_full(q)) return -1;

    q->data[q->back] = item; // Place the item at the back of the queue
    q->back = (q->back + 1) % q->capacity; // Increment back index and wrap around if necessary
    q->size++; // Increment the size of the queue

    return 0; 
}


// Dequeue an item
// Returns the item at the front of the queue and
// removes an item from the queue.
// Removing from an empty queue should crash the program, call exit(1)
int queue_dequeue(queue_t *q){
    if (queue_empty(q)) exit(1); // If the queue is empty, exit program

    int item = q->data[q->front]; // Retrieve the item at the front of the queue
    q->front = (q->front + 1) % q->capacity; // Increment front index and wrap around if necessary
    q->size--; // Decrement the size of the queue

    return item; 
}

// Queue Size
// Queries the current size of a queue
// A queue that has not been previously created will crash the program.
// (i.e. A NULL queue cannot return the size, call exit(1))
unsigned int queue_size(queue_t* q){
    // If the queue is NULL, exit program
    if (!q) exit(1); 
    return q->size; 
}


// Free queue
// Removes a queue and all of its elements from memory.
// This should be called before the proram terminates.
void free_queue(queue_t* q){
    free(q->data); // Free the memory allocated for the queue's data array
    free(q); // Free the memory allocated for the queue structure
}

//queue_peek
//It will return the first value in the queue without removing it
int queue_peek(queue_t* q) {
    if (queue_empty(q)) exit(1); // If the queue is empty, exit program
    return q->data[q->front]; 
}

//queue_back
//It will return the last value in the queue
int queue_back(queue_t* q) {
    if (queue_empty(q)) exit(1); // If the queue is empty, exit program
    // Calculate the index of the last item
    unsigned int backIndex = q->back == 0 ? q->capacity - 1 : q->back - 1;
    return q->data[backIndex]; 
}


//queue_equal
// Check if two queues are equal
int queue_equals(queue_t* q1, queue_t* q2) {
    // First, check if the sizes are the same
    if (q1->size != q2->size) {
        return 0; // The queues are not equal
    }
    // Since the queues are circular, we need to compare elements from front to back correctly
    for (unsigned int i = 0; i < q1->size; i++) {
        unsigned int index1 = (q1->front + i) % q1->capacity;
        unsigned int index2 = (q2->front + i) % q2->capacity;
        if (q1->data[index1] != q2->data[index2]) {
            return 0; // The queues are not equal
        }
    }
    return 1; // The queues are equal
}
#endif
