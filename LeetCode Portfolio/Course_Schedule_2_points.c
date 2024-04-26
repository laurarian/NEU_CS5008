// Rong Huang
// CS5008 Spring 2024
// 207. Course Schedule---Medium (2 points) Topics：DFS,BFS,Graph,Topological Sort
// https://leetcode.com/problems/course-schedule/description/

/**
 * Kahn's Algorithm for topological sorting:
 * - Calculates in-degrees for all vertices.
 * - Uses a queue to handle all vertices with zero in-degree.
 * - Decreases in-degrees of adjacent vertices, adding those at 0 to the queue.
 * - Continues until all vertices are processed or a cycle is detected, 
 * indicating whether all courses can be completed.
 * 
 * Complexity Analysis:
 * - Time Complexity: O(N + P), where P is the sum of operations for prerequisites, and N for queue.
 * - Space Complexity: O(N + P), where N accounts for the in-degree array and P for the adjacency list.
 */

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize) {
    // Initialize in-degrees and adjacency list for courses
    int* inDegrees = (int*)calloc(numCourses, sizeof(int));
    int** adjList = (int**)malloc(numCourses * sizeof(int*));
    int* adjSize = (int*)calloc(numCourses, sizeof(int));
    // Allocate space for each course's adjacency list
    for (int i = 0; i < numCourses; i++) {
        adjList[i] = (int*)malloc(numCourses * sizeof(int));
    }
    // Build the graph from prerequisites
    for (int i = 0; i < prerequisitesSize; i++) {
        int course = prerequisites[i][0];
        int prereq = prerequisites[i][1];
        adjList[prereq][adjSize[prereq]++] = course;
        inDegrees[course]++;
    }
    // Initialize queue for BFS
    int* queue = (int*)malloc(numCourses * sizeof(int));
    int front = 0, rear = 0;
    
    // Enqueue courses with zero in-degree
    for (int i = 0; i < numCourses; i++) {
        if (inDegrees[i] == 0) {
            queue[rear++] = i;
        }
    }
    // Process the queue
    int count = 0;
    while (front < rear) {
        int curr = queue[front++];
        count++;
        for (int j = 0; j < adjSize[curr]; j++) {
            int next = adjList[curr][j];
            if (--inDegrees[next] == 0) {
                queue[rear++] = next;
            }
        }
    }
    return count == numCourses; // Check if all courses can be completed.
}