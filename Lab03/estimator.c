// Rong Huang
// 2/12/2024
// CS5008 Lab03
//
// Implement your cycle count tool here.
// Reading in files line by line
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to remove leading spaces and tabs
void removeLeadingSpaces(char* str) {
    int index = 0;
    while (str[index] == ' ' || str[index] == '\t') {
        index++;
    }
    if (index != 0) {
        int i = 0;
        while (str[i + index] != '\0') {
            str[i] = str[i + index];
            i++;
        }
        str[i] = '\0'; // Terminate the modified string
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./estimator <assembly_file.s>\n");
        return 1;
    }

    // Open the assembly file for reading
    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }


    // Initialize counters for each instruction type
    int add_count = 0, sub_count = 0, mul_count = 0, div_count = 0;
    int mov_count = 0, lea_count = 0, push_count = 0, pop_count = 0, ret_count = 0;
    int total_cycles = 0, total_instructions = 0;

    char line[1024]; // Buffer to store each line read from the file

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        removeLeadingSpaces(line); // Remove leading spaces for accurate instruction matching

        // Use strncasecmp for case-insensitive comparison
        if (strncasecmp(line, "add", 3) == 0) { add_count++; total_cycles += 1; }
        else if (strncasecmp(line, "sub", 3) == 0) { sub_count++; total_cycles += 1; }
        else if (strncasecmp(line, "mul", 3) == 0 || strncasecmp(line, "imul", 4) == 0) { mul_count++; total_cycles += 3; }
        else if (strncasecmp(line, "div", 3) == 0 || strncasecmp(line, "idiv", 4) == 0) { div_count++; total_cycles += 24; }
        else if (strncasecmp(line, "mov", 3) == 0) { mov_count++; total_cycles += 1; }
        else if (strncasecmp(line, "lea", 3) == 0) { lea_count++; total_cycles += 3; }
        else if (strncasecmp(line, "push", 4) == 0) { push_count++; total_cycles += 1; }
        else if (strncasecmp(line, "pop", 3) == 0) { pop_count++; total_cycles += 1; }
        else if (strncasecmp(line, "ret", 3) == 0) { ret_count++; total_cycles += 1; }
    }

    fclose(file);

    // Print the counts and total cycles
    printf("Instruction counts:\n");
    printf("ADD: %d\n", add_count);
    printf("SUB: %d\n", sub_count);
    printf("MUL: %d\n", mul_count);
    printf("DIV: %d\n", div_count);
    printf("MOV: %d\n", mov_count);
    printf("LEA: %d\n", lea_count);
    printf("PUSH: %d\n", push_count);
    printf("POP: %d\n", pop_count);
    printf("RET: %d\n", ret_count);
    printf("\nTotal Instructions: %d\nTotal Cycles: %d\n", add_count + sub_count + mul_count + div_count + mov_count + lea_count + push_count + pop_count + ret_count, total_cycles);

    return 0;
}




