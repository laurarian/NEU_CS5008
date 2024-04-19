#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <signal.h>


#include "my_dll.h"
#include "my_graph.h"
#include "my_pq.h"

#define CITY_COUNT 19

typedef struct City {
    char name[20];
    int number;
} city_t;

city_t cities[CITY_COUNT] = {
    {"Amsterdam", 0}, {"Belgrade", 1}, {"Berlin", 2},
    {"Bern", 3}, {"Brussels", 4}, {"Budapest", 5},
    {"Copenhagen", 6}, {"Genoa", 7}, {"Hamburg", 8},
    {"Lisbon", 9}, {"Madrid", 10}, {"Munich", 11},
    {"Naples", 12}, {"Paris", 13}, {"Prague", 14},
    {"Rome", 15}, {"Trieste", 16}, {"Vienna", 17},
    {"Warsaw", 18}
};

void segfault_handler(int signal)
{
    printf("Segmentation fault occurred.\n");
}

//The Dijkstra algorithm for shortest path map
void dijkstra(graph_t* g, int map[19][19], int source, int dest) {
    int i;
    int dist[19];
    int prev[19];
    for (i = 0; i < 19; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[source] = 0;
    pq_t* q = create_pq(CITY_COUNT);  //  CITY_COUNT
    graph_node_t* node1 = find_node(g, source);
    pq_insert(q, node1, 0);  // Initial insert with cost 0

    while (!pq_is_empty(q)) {
        graph_node_t* minNode = pq_remove_min(q);;
        node_t* currEdge = minNode->outNeighbors->head;
        while (currEdge != NULL) {
            graph_node_t* neighborNode = ((graph_edge_t*)currEdge->data)->destination;  
            int new_cost = dist[minNode->data] + ((graph_edge_t*)currEdge->data)->weight;
            if (dist[neighborNode->data] > new_cost) {
                dist[neighborNode->data] = new_cost;
                prev[neighborNode->data] = minNode->data;
                pq_insert(q, neighborNode, new_cost);  
            }
            currEdge = currEdge->next;
        }
    }
    // Print shortest path from source to destination
    int curr = dest;
    int path[19];
    int path_length = 0;
    while (curr != -1) {
        path[path_length] = curr;
        path_length++;
        curr = prev[curr];
    }

    // Print results 
    printf("ORIGIN: %s\n", cities[source].name);
    printf("DESTINATION: %s\n", cities[dest].name);
    if (dist[dest] == INT_MAX) {
        printf("No path found.\n");
    } else {
        printf("LENGTH: %d\n", dist[dest]);
        printf("PATH CITIES:");
        for (i = path_length - 1; i >= 0; i--) {
            printf(" %s", cities[path[i]].name);
        }
        printf("\n");
    }

    free_pq(q);
}

int main() {
	//Read data from datafile city.dat
	FILE *cit;
	cit = fopen("city.dat","r");
	char city1[19], city2[19];
	int distance;

	graph_t* map = create_graph();

	int i;
	for(i =0;i<19;i++){
		graph_add_node(map,i);
	}
	
	//Build an adjacency matrix based on the city.dat datafile
	int matrix[19][19] = {0};
	
    while (fscanf(cit, "%s %s %d", city1, city2, &distance) != EOF) {
        int m,n = -1;
		int k;
		for(k = 0; k< 19; k++){
			if (strcmp(cities[k].name,city1) == 0){m = cities[k].number;}
			if (strcmp(cities[k].name,city2) == 0){n = cities[k].number;}
		}
		if(m != -1 && n != -1){
			graph_add_edge(map,m,n,distance);
            graph_add_edge(map,n,m,distance);
			matrix[m][n] = distance;
			matrix[n][m] = distance;

		}
    }

    fclose(cit);

	//Create an alphabetized list of cities for selection by the user
	int ori = -100000;
	int des = -100000;
	
	while(ori != 0 && des != 0){
		printf("Please select an origin city\nEnter a number associated with one of the cities below:\n");
		for(i = 0; i< 19; i++){
    		printf("%-15s ---  %2d\n", cities[i].name, cities[i].number + 1);
		}
		printf("\nTO QUIT ENTER   ---  0\n");
		scanf("%d",&ori);
		if(ori == 0){exit(1);}

		printf("Please select an destination city:\n");
		for(i = 0; i< 19; i++){
			if (cities[i].number != ori) { 
    			printf("%-15s ---  %2d\n", cities[i].name, cities[i].number + 1);}
		}
		printf("\nTO QUIT ENTER   ---  0\n");
		scanf("%d",&des);
		if(des == 0){exit(1);}

		dijkstra(map,matrix,ori - 1, des - 1);
}
	free_graph(map);
    return EXIT_SUCCESS;
}
