/**
 * LeetCode 2 - Add Two Numbers
 * https://leetcode.com/problems/add-two-numbers/
 * Difficulty: Medium
 *
 * Problem:
 * You are given two non-empty linked lists representing two non-negative
 * integers. The digits are stored in reverse order and each node contains a
 * single digit. Add the two numbers and return the sum as a linked list (also
 * in reverse order). The numbers do not contain leading zeros except for 0.
 *
 * Approach:
 * Walk both lists in parallel summing digit by digit while tracking a carry.
 * A dummy head node lets us append result nodes without special-casing the
 * first node. Continue while either list has remaining nodes OR there is a
 * pending carry (handles the extra leading digit, e.g. 5 + 5 = 10).
 *
 * Complexity:
 * - Time: O(max(n, m)) where n, m are the lengths of the two lists.
 * - Space: O(max(n, m)) for the output list (not counting input/output).
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0); // sentinel
        ListNode* curr = dummy;
        int carry = 0;

        // Keep going while there are digits left or a carry remains.
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int sum = carry;
            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }
            carry = sum / 10;
            curr->next = new ListNode(sum % 10);
            curr = curr->next;
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
    // l1 = [2,4,3] (342), l2 = [5,6,4] (465) => [7,0,8] (807)
    ListNode* l1 = buildList({2, 4, 3});
    ListNode* l2 = buildList({5, 6, 4});
    ListNode* r = sol.addTwoNumbers(l1, l2);
    for (int v : toVector(r)) cout << v << " ";
    cout << endl;

    // l1 = [0], l2 = [0] => [0]
    ListNode* r2 = sol.addTwoNumbers(buildList({0}), buildList({0}));
    for (int v : toVector(r2)) cout << v << " ";
    cout << endl;
    return 0;
}
