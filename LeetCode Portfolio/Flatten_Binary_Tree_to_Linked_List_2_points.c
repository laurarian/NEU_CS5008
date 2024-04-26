// Rong Huang
// CS5008 Spring 2024
// 114. Flatten Binary Tree to Linked List---Medium (2 points) Topics：Tree,LinkedList,DFS
// https://leetcode.com/problems/flatten-binary-tree-to-linked-list/

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/** DFS(preorder traversal): root,left,right
 * We use the following steps following preorder traversal:
 * 1. Shift the Left Subtree: Transform the left subtree of each node into the right subtree.
 * 2. Attach the Right Subtree: Connect the original right subtree to the farthest right node of the new right subtree.
 * 3. Iterate: Continue this method for each node, moving from one to the next, until no nodes remain.
 * since the order is the same with the preorder traversal,so it can be successful.
 * 
 * Complexity:
 * - Time: O(n), as each node in the tree is visited just once and only simple operations are performed on each.
 * - Space: O(1), since we're altering the tree directly without using extra space.
 */

// iterative
void flatten(struct TreeNode* root) {
    // Iterate through the tree starting from the root until the node is NULL
    while(root != NULL) {
        // Check if there is a left child; if not, simply move to the right child
        if (root->left == NULL) {
            root = root->right;
        } else {
            // Initialize 'pre' to find the farthest right node of the left subtree
            struct TreeNode* pre = root->left;
            // Traverse to the rightmost node of the left subtree
            while (pre->right != NULL) {
                pre = pre->right; // Move right until the end of the subtree
            }
            // Attach the current node's right subtree to the rightmost node of 
            // the left subtree
            pre->right = root->right;
            // Move the left subtree to replace the right subtree
            root->right = root->left;
            // Set the left pointer to NULL since the linked list should only 
            // have right pointers
            root->left = NULL;
            // Proceed to the new right subtree, which is the former left subtree
            root = root->right;
        }
    }
}
