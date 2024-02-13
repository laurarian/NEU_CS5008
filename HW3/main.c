// Rong Huang
// 2/13/2024
// Homework Assignment 3
//
// Compile this assignment with: gcc -g -Wall main.c -o main
// Use this file to implement testing for your
// doubly linked list implementation
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_dll.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

// Function prototypes for test cases
int testCreationAndDeletion();
int testPushFrontAndBack();
int testPopFrontAndBack();
int testInsertAndRemove();
int testSize();

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main() {
    int passedTests = 0;
    int totalTests = 5; // Adjust based on the number of test functions

    // Test 1: Creation and Deletion of DLL
    passedTests += testCreationAndDeletion();

    // Test 2: Pushing to Front and Back
    passedTests += testPushFrontAndBack();

    // Test 3: Popping from Front and Back
    passedTests += testPopFrontAndBack();

    // Test 4: Insertion and Removal at Arbitrary Positions
    passedTests += testInsertAndRemove();

    // Test 5: Checking the Size of the DLL
    passedTests += testSize();

    // Print test summary
    printf("Passed %d out of %d tests.\n", passedTests, totalTests);

    return 0;
}

int testCreationAndDeletion() {
    dll_t* dll = create_dll();
    if (!dll || dll_size(dll) != 0) {
        printf("Test 1 Failed: Error in DLL creation or initial size is not 0.\n");
        free_dll(dll); // Ensure we clean up even if the test fails
        return 0;
    }
    free_dll(dll);
    printf("Test 1 Passed: DLL creation and deletion.\n");
    return 1;
}

int testPushFrontAndBack() {
    dll_t* dll = create_dll();
    dll_push_front(dll, 1);
    dll_push_back(dll, 2);
    if (dll_size(dll) != 2 || dll_pop_front(dll) != 1 || dll_pop_back(dll) != 2) {
        printf("Test 2 Failed: Error in pushing or popping front/back.\n");
        free_dll(dll);
        return 0;
    }
    free_dll(dll);
    printf("Test 2 Passed: Pushing and popping front/back.\n");
    return 1;
}

int testPopFrontAndBack() {
    dll_t* dll = create_dll();
    dll_push_front(dll, 1);
    dll_push_back(dll, 2);
    int front = dll_pop_front(dll);
    int back = dll_pop_back(dll);
    if (front != 1 || back != 2 || !dll_empty(dll)) {
        printf("Test 3 Failed: Error in popping front/back or DLL not empty afterwards.\n");
        free_dll(dll);
        return 0;
    }
    free_dll(dll);
    printf("Test 3 Passed: Correctly popped front and back.\n");
    return 1;
}

int testInsertAndRemove() {
    dll_t* dll = create_dll();
    dll_push_back(dll, 1); // 1
    dll_insert(dll, 1, 2); // 1, 2
    dll_push_front(dll, 0); // 0, 1, 2
    if (dll_size(dll) != 3 || dll_remove(dll, 1) != 1 || dll_size(dll) != 2) {
        printf("Test 4 Failed: Error in insertion or removal.\n");
        free_dll(dll);
        return 0;
    }
    free_dll(dll);
    printf("Test 4 Passed: Insertion and removal at arbitrary positions.\n");
    return 1;
}

int testSize() {
    dll_t* dll = create_dll();
    for (int i = 0; i < 5; i++) {
        dll_push_back(dll, i);
    }
    if (dll_size(dll) != 5) {
        printf("Test 5 Failed: DLL size incorrect.\n");
        free_dll(dll);
        return 0;
    }
    free_dll(dll);
    printf("Test 5 Passed: Correct DLL size reported.\n");
    return 1;
}

