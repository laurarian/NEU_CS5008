// Modify this file
// compile with: gcc linkedlist.c -o linkedlist
// TODO: RongHuang
// TODO: 1/26/2024
// Lab02 CS5008 Fall 2023

#include <stdio.h>
#include <stdlib.h> // contains the functions free/malloc

// TODO: Write your functions here
// There should be 1.) create_list 2.) print_list 3.) free_list
// You may create as many helper functions as you like.

// TODO: Create your node_t type here
typedef struct node
{
	int wins;
	int year;
	struct node *next;
} node_t;

// Function create_list,all the data will be assignment in the function,it include
// allocate the memory,create the node,link the nodes.
node_t *create_list()
{
	// allocate the memory
	node_t *node1 = malloc(sizeof(node1));
	node_t *node2 = malloc(sizeof(node2));
	node_t *node3 = malloc(sizeof(node3));
	node_t *node4 = malloc(sizeof(node4));
	node_t *node5 = malloc(sizeof(node5));

	// assigne the data to each node
	node1->wins = 108;
	node1->year = 2018;
	node2->wins = 93;
	node2->year = 2017;
	node3->wins = 93;
	node3->year = 2016;
	node4->wins = 78;
	node4->year = 2015;
	node5->wins = 71;
	node5->year = 2014;

	// link each node into the list
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = NULL; // End of the list

	return node1; // return the head of the list
}

// Function to print the list
void print_list(node_t *head)
{
	node_t *current = head;
	while (current != NULL)
	{
		printf("%d, %d wins\n", current->year, current->wins);
		current = current->next; // Move to the next node
	}
}

// Function to free the memory allocated for the list
void free_list(node_t *head)
{
	node_t *temp;
	while (head != NULL)
	{
		temp = head;	   // Hold reference to current node
		head = head->next; // Move to the next node
		free(temp);		   // Free the current node
	}
}

int main()
{
	// TODO: Implement me!
	node_t *head = create_list();
	print_list(head);
	free_list(head);

	return 0;
}

