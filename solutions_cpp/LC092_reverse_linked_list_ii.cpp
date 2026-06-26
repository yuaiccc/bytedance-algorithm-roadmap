/**
 * LeetCode 92 - Reverse Linked List II
 * https://leetcode.com/problems/reverse-linked-list-ii/
 * Difficulty: Medium
 *
 * Problem:
 * Given the head of a singly linked list and two integers left and right where
 * left <= right, reverse the nodes of the list from position left to position
 * right, and return the reversed list. (Positions are 1-indexed.)
 *
 * Approach:
 * Use a dummy head node to simplify edge cases (e.g. left == 1). Move a
 * pointer `prev` to the node immediately before position `left`. Then perform
 * head-insertion: repeatedly take the node after `curr` and move it right
 * after `prev`. After (right - left) such insertions the [left, right] range
 * is reversed in-place.
 *
 * Complexity:
 * - Time: O(n) — single pass to locate `prev`, then (right-left) insertions.
 * - Space: O(1) — only a constant number of pointers.
 */

#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        // Dummy head so we never have to special-case left == 1.
        ListNode* dummy = new ListNode(0, head);
        ListNode* prev = dummy;

        // Move prev to the node just before position `left`.
        for (int i = 1; i < left; ++i) {
            prev = prev->next;
        }

        // `curr` is the first node of the range to reverse.
        ListNode* curr = prev->next;

        // Head-insertion: move the node after `curr` to right after `prev`.
        // After each iteration the reversed prefix grows by one.
        for (int i = 0; i < right - left; ++i) {
            ListNode* nxt = curr->next;       // node to move
            curr->next = nxt->next;           // unlink nxt
            nxt->next = prev->next;           // insert at front of range
            prev->next = nxt;
        }

        return dummy->next;
    }
};

// ---- Helper functions for local testing ----
ListNode* buildList(const vector<int>& vals) {
    ListNode* dummy = new ListNode(0);
    ListNode* tail = dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy->next;
}

vector<int> toVector(ListNode* head) {
    vector<int> res;
    for (ListNode* p = head; p; p = p->next) res.push_back(p->val);
    return res;
}

int main() {
    Solution sol;
    // head = [1,2,3,4,5], left = 2, right = 4  =>  [1,4,3,2,5]
    ListNode* h = buildList({1, 2, 3, 4, 5});
    ListNode* r = sol.reverseBetween(h, 2, 4);
    for (int v : toVector(r)) cout << v << " ";
    cout << endl;

    // head = [5], left = 1, right = 1  =>  [5]
    ListNode* h2 = buildList({5});
    ListNode* r2 = sol.reverseBetween(h2, 1, 1);
    for (int v : toVector(r2)) cout << v << " ";
    cout << endl;
    return 0;
}
