// Rong Huang
// CS5008 Spring 2024
// 406. Queue Reconstruction by Height---Medium (2 points) Topics：Array,Binary Indexed Tree,Segment Tree,Sorting
// https://leetcode.com/problems/queue-reconstruction-by-height/description/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

// Comparison function for sorting; sorts by height descending, then by k ascending if heights are the same.
int cmp(int** a, int** b) {
    if (a[0][0] != b[0][0]) {
        return (b[0][0] - a[0][0]);  // Higher height comes first
    } else {
        return (a[0][1] - b[0][1]);  // If heights are equal, order by k ascending
    }
}

// Shifts elements of the array one position to the right from 'left' to 'right', excluding the last position.
void moveBack(int** people, int left, int right) {
    for (int i = right; i > left; i--) {
        people[i] = people[i - 1];
    }
}

// Reconstructs the queue based on the provided conditions.
int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = peopleSize;  // Set the return size
    *returnColumnSizes = malloc(sizeof(int) * peopleSize);  // Allocate space for column sizes
    for (int i = 0; i < peopleSize; i++) { 
        (*returnColumnSizes)[i] = 2;  // Each person has 2 properties
    }

    qsort(people, peopleSize, sizeof(people[0]), cmp);  // Sort people using the custom comparison function

    for (int i = 0; i < peopleSize; i++) {
        int sit = people[i][1];  // The target index for the current person
        int* temp = people[i];  // Temporarily store the current person's data
        moveBack(people, sit, i);  // Move elements to make space for the current person
        people[sit] = temp;  // Place the current person in the correct position
    }

    return people;  // Return the reconstructed queue
}