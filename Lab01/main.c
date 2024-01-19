// Rong Huang
// 1/19/2024
// CS5008 Lab1 Writing our first C program
// This is a program to the power of a number and print the result

# include <stdio.h>

// Function to calculate power of a number
double power(double base, double n){
    double result = 1.0;

    // Calculate power using a loop
    for (int i = 0;i < n; i++){
        result *= base;

    }

    return result;
}

int main() {
    // Loop to compute and print powers of 2 from 1 to 10
    for (int i = 1; i <= 10; i++) {
        double result = power(2.0, (double)i);
        printf("power(2, %d) = %f\n", i, result);
    }

    return 0;

}


