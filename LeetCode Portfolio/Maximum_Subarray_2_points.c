// Rong Huang
// CS5008 Spring 2024
// 53. Maximum Subarray---Medium (2 points) Topics：Array,Dynamic Programming
// https://leetcode.com/problems/maximum-subarray/description/

/**
 * Approach: Dynamic Programming
 * - Use DP since it builds on previous results for optimal subproblem solutions.
 * 1. DP Array: dp[i] stores the max subarray sum ending at index i.
 * 2. Recurrence: dp[i] = max(dp[i-1] + nums[i], nums[i])
 *    Reset to nums[i] if dp[i-1] < 0, as it does not aid in maximizing the sum.
 * 3. Initialize: Start dp[0] with nums[0], the only value at index 0.
 * 4. Traverse: Loop through the array from start to end to fill dp array.
 * 
 * - Time Complexity: O(n), since each element is processed exactly once to calculate the maximum sum.
 * - Space Complexity: O(n), due to the storage of an array holding the maximum sum for each index.
 */

// Dynamic programming solution
#define max(a,b) ((a) > (b) ? (a) : (b)) // Define max as a macro

int maxSubArray(int* nums, int numsSize) {
    // Array to store the max subarray sum ending at each index
    int dp[numsSize]; 
    dp[0] = nums[0]; // Initialize the dp[0]
    // If numsSize is 1, nums[0] should be returned directly.
    int subArrSum = dp[0]; 
    for (int i = 1; i < numsSize; i++){
        // update the dp array
        dp[i] = max(dp[i - 1] + nums[i], nums[i]);

        //If dp[i] is greater than the subArrSum,update it
        if (dp[i] > subArrSum) 
            subArrSum = dp[i];
    }
    return subArrSum;
}