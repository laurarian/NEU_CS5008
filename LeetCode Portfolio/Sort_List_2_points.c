// Rong Huang
// CS5008 Spring 2024
// 148. Sort List---Medium (2 points) Topics：LinkedList,Divide and Conquer,Merge Sort
// https://leetcode.com/problems/sort-list/description/

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

// Merge two sorted linked lists into one sorted linked list
struct ListNode* merge(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode* head = malloc(sizeof(struct ListNode)); // Create a dummy head to facilitate the merging process
    struct ListNode *current = head, *first = list1, *second = list2;
    
    // Traverse both lists and append the smaller value to the merged list
    while (first != NULL && second != NULL) {
        if (first->val <= second->val) {
            current->next = first;
            first = first->next;
        } else {
            current->next = second;
            second = second->next;
        }
        current = current->next;
    }
    
    // Attach the remaining part of list1 or list2 to the merged list
    current->next = (first != NULL) ? first : second;
    return head->next; // Return the head of the newly formed list
}

// Recursively split the list into halves and merge them in sorted order
struct ListNode* divideAndConquer(struct ListNode* start, struct ListNode* end) {
    if (start == NULL) {
        return NULL; // If the start is NULL, return NULL indicating empty list
    }
    if (start->next == end) {
        start->next = NULL; // Cut the connection to the rest of the list to form a valid end
        return start;
    }
    
    // Use fast and slow pointers to find the middle of the list
    struct ListNode *slow = start, *fast = start;
    while (fast != end) {
        slow = slow->next;
        fast = fast->next;
        if (fast != end) {
            fast = fast->next;
        }
    }
    struct ListNode* mid = slow; // Midpoint for divide
    struct ListNode* left = divideAndConquer(start, mid); // Recursively sort the left half
    struct ListNode* right = divideAndConquer(mid, end); // Recursively sort the right half
    
    // Merge the sorted halves
    return merge(left, right);
}

// Main function to sort the linked list using merge sort
struct ListNode* sortList(struct ListNode* head) {
    return divideAndConquer(head, NULL); // Start sorting from the head to the end (NULL)
}
