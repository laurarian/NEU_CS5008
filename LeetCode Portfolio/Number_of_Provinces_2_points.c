// Rong Huang
// CS5008 Spring 2024
// 547. Number of Provinces---Medium (2 points) Topics：DFS,BFS,Graph,Union Find
// https://leetcode.com/problems/number-of-provinces/description/

/**
 * Using DFS to count provinces in a graph represented by an adjacency matrix:
 * - Maintain a 'visited' array to keep track of explored cities.
 * - Initiate a DFS for each unvisited city:
 *   1. Mark as visited.
 *   2. Recursively visit all directly connected cities.
 *   3. Each DFS initiation from an unvisited city marks a new province.
 * Complexity:
 * - Time: O(n^2), due to potential DFS across all entries in the n x n matrix.
 * - Space: O(n), needed for the visited tracker and recursion stack depth.
 */

// Define the DFS function to explore connected cities
void dfs(int** isConnected, int* visited, int cities, int i) {
    // Loop through all possible cities to find connected ones
    for (int j = 0;j < cities; j++) {
        // If city 'j' is connected and unvisited
        if (isConnected[i][j] == 1 && !visited[j]) {
            visited[j] = 1; // Mark city 'j' as visited
            // Recursively call dfs to explore all cities connected to 'j'
            dfs(isConnected, visited, cities, j);
        }
    }
}

// Define the function to count connected components (provinces) in the graph
int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize) {
    int cities = isConnectedSize; // Total number of cities
    int visited[cities]; // Track visited cities
    memset(visited, 0, sizeof(visited)); // Initialize visited array to false
    int provinces = 0; // Counter for provinces

    // Loop through cities to initiate DFS on unvisited ones
    for (int i = 0; i < cities; i++) {
        if (!visited[i]) { // New province found
            dfs(isConnected, visited, cities, i); // Start DFS
            provinces++; // Increment province count
        }
    }
    return provinces; // Return the count of provinces
}
