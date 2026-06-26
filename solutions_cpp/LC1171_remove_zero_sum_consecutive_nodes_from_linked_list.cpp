/**
 * LeetCode 1171 - Remove Zero Sum Consecutive Nodes from Linked List
 * https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/
 * Difficulty: Medium
 *
 * Problem:
 * Given the head of a linked list, repeatedly delete consecutive sequences of
 * nodes that sum to 0 until no such sequences exist. Return the resulting head.
 * (You may return any valid answer.)
 *
 * Approach:
 * Use a running prefix sum with a hash map.
 * 1) First pass: walk from the dummy head, accumulating the prefix sum. Store
 *    the LAST node at which each prefix sum occurs. (If a prefix sum repeats,
 *    the later occurrence overwrites the earlier one.)
 * 2) Second pass: walk again from the dummy head accumulating the prefix sum.
 *    For each node, set its `next` to skip straight to prefix[sum]->next,
 *    which removes the entire zero-sum run between the two equal prefix sums.
 * The dummy head (value 0) guarantees that a zero-sum run starting at the
 * real head is handled, since prefix 0 maps back to the dummy.
 *
 * Complexity:
 * - Time: O(n) — two linear passes over the list.
 * - Space: O(n) — for the prefix-sum hash map.
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
    ListNode* removeZeroSumSublists(ListNode* head) {
        ListNode* dummy = new ListNode(0, head);
        unordered_map<int, ListNode*> prefix;
        int sum = 0;

        // First pass: record the last node seen for each prefix sum.
        for (ListNode* node = dummy; node != nullptr; node = node->next) {
            sum += node->val;
            prefix[sum] = node;
        }

        // Second pass: reconnect, skipping zero-sum runs.
        sum = 0;
        for (ListNode* node = dummy; node != nullptr; node = node->next) {
            sum += node->val;
            // Jump to the node after the last occurrence of this prefix sum,
            // deleting every node in between (they sum to zero).
            node->next = prefix[sum]->next;
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
    // head = [1,2,-3,3,1] => [3,1]  (or [1,2,1])
    ListNode* h = buildList({1, 2, -3, 3, 1});
    ListNode* r = sol.removeZeroSumSublists(h);
    for (int v : toVector(r)) cout << v << " ";
    cout << endl;

    // head = [1,2,3,-3,4] => [1,2,4]
    ListNode* h2 = buildList({1, 2, 3, -3, 4});
    ListNode* r2 = sol.removeZeroSumSublists(h2);
    for (int v : toVector(r2)) cout << v << " ";
    cout << endl;
    return 0;
}
