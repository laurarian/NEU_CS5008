// Rong Huang
// 04/08/2024
// Lab09
//
// Compile with: gcc -Wall pascal.c -o pascal
// Run with: ./pascal 32

#include <stdio.h>
#include <stdlib.h>

#define LARGEST_TRIANGLE 33

// calculate and return the i-th row of Pascal's Triangle
// rowIndex = the index of the row that should be calculated
// returnSize = the size of the row that was calculated
// returns a pointer to an array of size `returnSize`,
//    assume that the caller calls free on the returned array
//
// coincidentally, this problem is the same as one of the problems
// on LeetCode: https://leetcode.com/problems/pascals-triangle-ii/
int *getRow(int rowIndex, int *returnSize)
{
    // TODO: Implement me!!
    if (returnSize == NULL) {return NULL;}
    *returnSize = rowIndex + 1; // The size of the row is rowIndex + 1
    int *row = (int *)malloc(*returnSize * sizeof(int));
    if (row == NULL) {
        *returnSize = 0;
        return NULL;
    }

    row[0] = 1; // The first element of each row is always 1

    // Calculate values for the row using memoization
    for (int i = 1; i <= rowIndex; i++)
    {
        row[i] = 1; // The last element of each row is also 1
        for (int j = i - 1; j > 0; j--)
        {
            // Update the value of current element by summing
            // the two directly above it, so we update it from right to left
            row[j] = row[j] + row[j - 1];
        }   
    }
    return row; // Return the pointer to the row
}

int main(int argc, char *argv[])
{
    // Make sure that there is one argument
    if (argc != 2)
    {
        printf("One argument expected: ./pascal 42\n");
        return 1;
    }

    // Convert the argument of the program into an integer
    // and make sure that it is between 0 and LARGEST_TRIANGLE - 1
    const int row = atoi(argv[1]);
    if (row < 0 || row > LARGEST_TRIANGLE - 1)
    {
        printf("row must between 0 and %d (inclusive)\n", LARGEST_TRIANGLE - 1);
        return 1;
    }

    int size = 0;
    int *row_values = getRow(row, &size);
    int i;

    printf("Row %d of Pascal's Triangle\n", row);
    for (i = 0; i < size; i++)
    {
        printf("%d ", row_values[i]);
    }
    printf("\n");

    // free the memory that was returned from function
    free(row_values);
    return 0;
}
