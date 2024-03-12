// Rong Huang
// 03/10/2024
// CS5008 Lab06
// gcc -Wall factorial.c -o factorial
// ./factorial

#include <stdio.h>

// Iterative version to calculate the factorial
unsigned long long int factorial(unsigned int n)
{
    // TODO: Implement iterative solution here
    // Initialize result to 1, factorial of 0 and 1 are 1.
    unsigned long long int result = 1;
	for(unsigned int i = n; i > 0; i--){
		result = result * i;
	}
	return result;
};

// Recursive version to calculate the factorial
unsigned long long int factorial_rec(unsigned int n)
{
    // Base case: if n is 0 or 1, the factorial is 1.
  	if(n == 0 || n == 1) {
		return 1;
	}
    // Recursion step: n! = n * (n-1)!
    return n * factorial_rec(n - 1);
}

int main()
{

    // Both of these should print the same result!
    // Use %llu for unsigned long long
    printf("factorial(16) = %llu\n", factorial(16)); 
    printf("factorial_rec(16) = %llu\n", factorial_rec(16)); 

    return 0;
}
