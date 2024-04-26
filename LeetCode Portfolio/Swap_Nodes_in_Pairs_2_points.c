// Rong Huang
// CS5008 Spring 2024
// 24. Swap Nodes in Pairs---Medium (2 points) Topics：LinkedList
// https://leetcode.com/problems/swap-nodes-in-pairs/description/

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

/** an iterative approach:
 * - Begin with a dummy node linked to the head to simplify list manipulation.
 * - Use a 'curr' pointer just before the nodes we need to swap.
 * - Swap each pair by:
 *   1. Linking 'curr' to 'second', then 'second' to 'first'.
 *   2. Link 'first' to the node after 'second'.
 *   3. Advance 'curr' to 'first' for the next pair.
 * 
 * Complexity:
 * Time Complexity: O(n), where n is the number of nodes in the list. Each node is visited once for re-linking.
 * Space Complexity: O(1), because we're only using a few pointers to rearrange the links.
 */
struct ListNode* swapPairs(struct ListNode* head) {
    // Create a dummy node to simplify handling of edge cases
    struct ListNode *dummy = malloc(sizeof(struct ListNode));
    dummy->next = head;   // Link dummy to the head of the list
    // Use 'curr' to track the node before the pair to swap
    struct ListNode *curr = dummy;
    // Loop as long as there are pairs to swap
    while (curr->next && curr->next->next) {
        // Identify the two nodes to swap
        struct ListNode *first = curr->next;        // First node of the pair
        struct ListNode *second = curr->next->next; // Second node of the pair
        // Execute the swap
        curr->next = second;
        first->next = second->next;
        second->next = first;
        // Move 'curr' to position for the next potential swap
        curr = first;
    }
    // Capture the new head to return
    struct ListNode* newHead = dummy->next;
    // Free the dummy node
    free(dummy);
    // Return the modified list head
    return newHead;
}
