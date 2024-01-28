// Rong Huang
// 1/28/2024

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    const int MAX_ROUNDS = 5;
    const int MAX_NUMBER = 10;

    // Seed the random number generator
    srand(time(NULL));

    // Array to store the number of guesses for each round
    int guesses[MAX_ROUNDS];

    printf("Welcome to the Guessing Game!\n");

    // Play the game for MAX_ROUNDS times
    for (int round = 0;round < MAX_ROUNDS;round++){
        // Generate a random number between 1 and MAX_NUMBER
        int number = rand() % 10 + 1;
        int guess = 0;
	int num_guesses = 0;

        printf("==========================\n");
        printf("CPU Says: Pick a number 1-%d\n", MAX_NUMBER);
        printf("==========================\n");

        // Continue until the correct guess is made
        while (guess != number) {
            printf("Make a guess:");
            scanf("%d", &guess);
            num_guesses++;

            if(guess < number) {
                printf("No guess higher!\n");
            }else if(guess > number) {
                printf("No guess lower!\n");
            }
        }

        printf("You got it!\n");
        guesses[round] = num_guesses;// Store the number of guesses for this round
    }

    // Print the summary of results
    printf("=================================================\n");
    printf("|Here are the results of your guessing abilities|\n");
    printf("=================================================\n");

    for (int i = 0;i<MAX_ROUNDS;i++ ) {
        printf("Game %d took you %d guesses\n",i,guesses[i]);     
    }

    return 0;
}

