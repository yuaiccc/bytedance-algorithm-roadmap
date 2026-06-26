/**
 * LeetCode 316 - Remove Duplicate Letters
 * https://leetcode.com/problems/remove-duplicate-letters/
 * Difficulty: Medium
 *
 * Problem:
 * Given a string s, remove duplicate letters so that every letter appears once
 * and only once. You must make sure your result is the smallest in
 * lexicographical order among all possible results. The result must also
 * preserve the original relative order as much as possible (i.e. it is a
 * subsequence of s).
 *
 * Approach:
 * Greedy monotonic stack. We want the lexicographically smallest subsequence
 * containing each distinct character exactly once. Maintain a stack of chosen
 * characters and a boolean array `inStack` to avoid duplicates. For each char c:
 *   - If c is already in the stack, skip it (it's a duplicate).
 *   - Otherwise, while the stack is non-empty, the top is greater than c (so
 *     popping it would improve the result), and the top character still appears
 *     later in the string (lastIdx[top] > current index), pop it and mark it
 *     as removed. This condition guarantees we can re-add it later.
 *   - Push c and mark it inStack.
 * We precompute the last occurrence index of each character to know whether a
 * character will appear again.
 *
 * Complexity:
 * - Time: O(n) — each character is pushed/popped at most once.
 * - Space: O(1) for the alphabet-sized structures, O(n) for the stack.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        // Last occurrence index for each character.
        int lastIdx[26];
        memset(lastIdx, -1, sizeof(lastIdx));
        for (int i = 0; i < (int)s.size(); ++i) {
            lastIdx[s[i] - 'a'] = i;
        }

        bool inStack[26] = {false};
        string stack; // acts as the monotonic stack of chosen chars

        for (int i = 0; i < (int)s.size(); ++i) {
            char c = s[i];
            int idx = c - 'a';
            if (inStack[idx]) {
                continue; // already chosen this character
            }
            // Pop larger characters that will appear again later.
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
//     cout << s.removeDuplicateLetters("bcabc") << endl;   // "abc"
//     cout << s.removeDuplicateLetters("cbacdcbc") << endl; // "acdb"
//     return 0;
// }
