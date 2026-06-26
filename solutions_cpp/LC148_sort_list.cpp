/**
 * LeetCode 148 - Sort List
 * https://leetcode.com/problems/sort-list/
 * Difficulty: Medium
 *
 * Problem:
 * Given the head of a linked list, sort it in ascending order and return the
 * new head. The solution must run in O(n log n) time.
 *
 * Approach:
 * Top-down merge sort on the linked list.
 * 1) Split: use fast/slow pointers to find the middle node. The slow pointer
 *    starts at head and fast starts at head->next so that the left half is the
 *    smaller half when the length is even. Cut the list at `mid`.
 * 2) Recurse: sort the left half and the right half.
 * 3) Merge: merge two sorted lists by comparing heads and relinking.
 *
 * Complexity:
 * - Time: O(n log n) — standard merge sort recurrence.
 * - Space: O(log n) — recursion stack depth (one pointer frame per level).
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
    ListNode* sortList(ListNode* head) {
        // Base case: empty or single node is already sorted.
        if (head == nullptr || head->next == nullptr) return head;

        // Split the list into two halves.
        ListNode* mid = getMid(head);
        ListNode* rightHead = mid->next;
        mid->next = nullptr; // sever the link

        // Recursively sort both halves.
        ListNode* left = sortList(head);
        ListNode* right = sortList(rightHead);

        // Merge the sorted halves.
        return merge(left, right);
    }

private:
    // Find the middle node (end of the left half) using fast/slow pointers.
    ListNode* getMid(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next; // start fast ahead for stable split
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    // Merge two sorted lists, returning the merged head.
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* curr = dummy;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                curr->next = l1;
                l1 = l1->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }
        // Attach any remaining nodes.
        curr->next = (l1 != nullptr) ? l1 : l2;
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
    // head = [4,2,1,3] => [1,2,3,4]
    ListNode* h = buildList({4, 2, 1, 3});
    ListNode* r = sol.sortList(h);
    for (int v : toVector(r)) cout << v << " ";
    cout << endl;

    // head = [-1,5,3,4,0] => [-1,0,3,4,5]
    ListNode* h2 = buildList({-1, 5, 3, 4, 0});
    ListNode* r2 = sol.sortList(h2);
    for (int v : toVector(r2)) cout << v << " ";
    cout << endl;
    return 0;
}
