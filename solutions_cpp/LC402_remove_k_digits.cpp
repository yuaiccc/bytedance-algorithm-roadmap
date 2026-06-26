/**
 * LeetCode 402 - Remove K Digits
 * https://leetcode.com/problems/remove-k-digits/
 * Difficulty: Medium
 *
 * Problem:
 * Given string num representing a non-negative integer num, and an integer k,
 * return the smallest possible integer after removing k digits from num.
 *
 * Approach:
 * Greedy with a monotonic increasing stack. We want the result to be as small
 * as possible, which means we prefer smaller digits in more significant (left)
 * positions. So we scan left to right: while we still have removals left (k>0)
 * and the current digit is smaller than the top of the stack, pop the stack
 * (removing the larger, more significant digit) and decrement k. Then push the
 * current digit. After the scan, if k>0 still, remove from the end (the
 * remaining largest digits). Finally strip leading zeros; if empty, return "0".
 *
 * Complexity:
 * - Time: O(n) — each digit is pushed and popped at most once.
 * - Space: O(n) for the stack.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string removeKdigits(string num, int k) {
        // Use a string as a stack of characters.
        string stack;
        for (char ch : num) {
            // Remove larger preceding digits while we still have budget.
            while (k > 0 && !stack.empty() && stack.back() > ch) {
                stack.pop_back();
                k--;
            }
            stack.push_back(ch);
        }
        // If we still have removals, drop from the tail.
        while (k-- > 0) {
            stack.pop_back();
        }
        // Strip leading zeros.
        int start = 0;
        while (start < (int)stack.size() - 1 && stack[start] == '0') {
            start++;
        }
        string result = stack.substr(start);
        return result.empty() ? "0" : result;
    }
};

// Optional: quick test
// int main() {
//     Solution s;
//     cout << s.removeKdigits("1432219", 3) << endl; // "1219"
//     cout << s.removeKdigits("10200", 1) << endl;   // "200"
//     cout << s.removeKdigits("10", 2) << endl;      // "0"
//     return 0;
// }
