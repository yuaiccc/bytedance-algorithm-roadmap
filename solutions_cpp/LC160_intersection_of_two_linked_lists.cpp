/**
 * LeetCode 160 - Intersection of Two Linked Lists
 * https://leetcode.com/problems/intersection-of-two-linked-lists/
 * Difficulty: Easy
 *
 * Problem:
 * Given the heads of two singly linked-lists headA and headB, return the node
 * at which the two lists intersect. If the two linked lists have no
 * intersection at all, return nullptr. The lists are guaranteed to be
 * cycle-free.
 *
 * Approach:
 * Two pointers, pA and pB, start at headA and headB respectively. Each pointer
 * walks to the end of its list, then switches to the head of the OTHER list.
 * If the lists intersect, the pointers will meet at the intersection node after
 * at most (lenA + lenB) steps, because both pointers traverse the same total
 * number of nodes (lenA + lenB). If there is no intersection, both become
 * nullptr at the same time.
 *
 * Complexity:
 * - Time: O(n + m)
 * - Space: O(1)
 */

#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == nullptr || headB == nullptr) return nullptr;

        ListNode *pA = headA;
        ListNode *pB = headB;

        // When a pointer reaches the end of its list, redirect to the other
        // head. After at most two passes they either meet or both are null.
        while (pA != pB) {
            pA = (pA != nullptr) ? pA->next : headB;
            pB = (pB != nullptr) ? pB->next : headA;
        }
        return pA; // intersection node or nullptr
    }
};

// Optional: helper to build test lists omitted for brevity.
// int main() { return 0; }
