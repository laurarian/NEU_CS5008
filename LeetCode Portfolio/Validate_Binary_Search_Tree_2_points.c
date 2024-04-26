// Rong Huang
// CS5008 Spring 2024
// 98. Validate Binary Search Tree---Medium (2 points) Topics：Binary Tree,DFS,BFS
// https://leetcode.com/problems/validate-binary-search-tree/description/


/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Helper function to perform in-order traversal of the binary tree and store node values in an array.
void inOrderTraversal(struct TreeNode* root, int values[], int *size) {
    if (root != NULL) {
        inOrderTraversal(root->left, values, size);   // Traverse left subtree
        values[(*size)++] = root->val;               // Store the node value and increment the size
        inOrderTraversal(root->right, values, size); // Traverse right subtree
    }
}

// Function to determine if a binary tree is a valid binary search tree (BST).
bool isValidBST(struct TreeNode* root) {
    int values[10000]; // Array to hold node values during in-order traversal
    int size = 0;      // Initialize size of the array to zero

    // Perform in-order traversal to populate values array
    inOrderTraversal(root, values, &size); 

    // Check if the array of values is sorted in strictly increasing order
    for (int i = 0; i < size - 1; i++) {
        if (values[i] >= values[i + 1]) {
            return false; // Return false if any subsequent value is not greater than the previous
        }
    }

    return true; // Return true if the binary tree satisfies BST properties
}