// Rong Huang
// CS5008 Spring 2024
// 72. Edit Distance---Medium (2 points) Topics：String,Dynamic Programming
// https://leetcode.com/problems/edit-distance/description/


// A helper function to find the minimum of three numbers
int min(int a, int b, int c) {
    return (a < b ? (a < c ? a : c) : (b < c ? b : c));
}

// Calculate the minimum number of operations required to convert word1 to word2
int minDistance(char* word1, char* word2) {
    int len1 = strlen(word1), len2 = strlen(word2);
    int dp[len1 + 1][len2 + 1]; // DP table to store the minimum operations

    // Initialize base cases for converting to an empty string
    for (int i = 0; i <= len1; i++) dp[i][0] = i;
    for (int j = 0; j <= len2; j++) dp[0][j] = j;

    // Iterate over each character in both strings
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                // No operation required if characters are the same
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                // Calculate costs for deletion, insertion, and replacement
                // And take the minimum cost operation
                dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
            }
        }
    }
    
    return dp[len1][len2]; // The final cell contains the minimum operations
}
