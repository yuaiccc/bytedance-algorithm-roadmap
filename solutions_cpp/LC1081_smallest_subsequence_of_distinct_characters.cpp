/**
 * LeetCode 1081 - Smallest Subsequence of Distinct Characters
 * https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/
 * Difficulty: Medium
 *
 * Problem:
 * Return the lexicographically smallest subsequence of s that contains all the
 * distinct characters in s exactly once.
 *
 * Note: This problem is IDENTICAL to LeetCode 316 (Remove Duplicate Letters).
 * The same greedy monotonic-stack solution applies verbatim. We keep the code
 * here for completeness.
 *
 * Approach:
 * Greedy monotonic stack. Maintain a stack of chosen characters and a boolean
 * array `inStack` to avoid duplicates. For each char c:
 *   - If c is already in the stack, skip it (duplicate).
 *   - Otherwise, while the stack is non-empty, the top is greater than c (so
 *     popping improves the result), and the top character still appears later
 *     (lastIdx[top] > current index), pop it and unmark it.
 *   - Push c and mark it inStack.
 * Precompute the last occurrence index of each character to know whether it
 * will appear again.
 *
 * Complexity:
 * - Time: O(n)
 * - Space: O(1) alphabet-sized structures, O(n) stack.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string smallestSubsequence(string s) {
        // Identical algorithm to LC316 removeDuplicateLetters.
        int lastIdx[26];
        memset(lastIdx, -1, sizeof(lastIdx));
        for (int i = 0; i < (int)s.size(); ++i) {
            lastIdx[s[i] - 'a'] = i;
        }

        bool inStack[26] = {false};
        string stack;

        for (int i = 0; i < (int)s.size(); ++i) {
            char c = s[i];
            int idx = c - 'a';
            if (inStack[idx]) {
                continue;
            }
            while (!stack.empty() && stack.back() > c &&
                   lastIdx[stack.back() - 'a'] > i) {
                inStack[stack.back() - 'a'] = false;
                stack.pop_back();
            }
            stack.push_back(c);
            inStack[idx] = true;
        }
        return stack;
    }
};

// Optional: quick test
// int main() {
//     Solution s;
//     cout << s.smallestSubsequence("bcabc") << endl;    // "abc"
//     cout << s.smallestSubsequence("cbacdcbc") << endl; // "acdb"
//     return 0;
// }
