// Rong Huang
// CS5008 Spring 2024
// 179. Largest Number---Medium (2 points) Topics：Array,String,Greedy,Sorting
// https://leetcode.com/problems/largest-number/description/


/* Use a greedy algorithm to form the largest number possible from a 
 * list of integers. we can do it by sorting the numbers based on 
 * a custom comparator.It determines the order by comparing two potential
 * combinations (xy vs yx)to see which combination is larger and arrange 
 * them in the best order for the largest concatenated result.
 * 
 * Complexity:
 * - Time: O(n log n) due to the qsort(using quicksort) and O(n) for concatenating(iterate once).
 * - Space: O(n) for storing the result string, O(n) for storing the result string, 
 *  where 'n' is the total number of digits in the input numbers.
 *  since the space need matches the combined length of these digits.
 */

// Define a comparator function to determine the order of xy
unsigned long long cmp(int *x, int *y) {
    // Find the smallest power of ten greater than *x and *y.
    unsigned long long sx = 10, sy = 10;
    // Increment sx until it is greater than *x.
    while (sx <= *x) {
        sx *= 10;
    }
    // Increment sy until it is greater than *y.
    while (sy <= *y) {
        sy *= 10;
    }
    // Compare the concatenated results of yx and xy to determine order.
    return sx * (*y) + (*x) - sy * (*x) - (*y);
}

// Function to generate the largest number from a list of integers.
char* largestNumber(int* nums, int numsSize) {
    // Sort the array using a custom comparator.
    qsort(nums, numsSize, sizeof(int), cmp);
    // Handle the case where the highest number is zero, meaning all are zero.
    if (nums[0] == 0) {
        char *res = malloc(sizeof(char) * 2);
        res[0] = '0';
        res[1] = '\0';
        return res; // Return "0".
    }
    char* res = malloc(sizeof(char) * 1000); // Allocate memory for result string.
    char *p = res; // Pointer for appending numbers.
    // Concatenate sorted numbers into a single string.
    for (int i = 0; i < numsSize; i++) {
        sprintf(p, "%d", nums[i]); // Append number to string.
        p += strlen(p); // Move to end of the current string.
    }
    return res;
}