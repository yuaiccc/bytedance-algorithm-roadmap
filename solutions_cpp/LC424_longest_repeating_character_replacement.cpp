/**
 * LeetCode 424 - Longest Repeating Character Replacement
 * https://leetcode.com/problems/longest-repeating-character-replacement/
 * Difficulty: Medium
 *
 * Problem:
 * You are given a string s and an integer k. You can choose any character of
 * the string and change it to any other uppercase English character. You can
 * perform this operation at most k times. Return the length of the longest
 * substring containing the same letter you can get.
 *
 * Approach:
 * Sliding window over the string. Maintain a frequency count of characters in
 * the current window [left, right]. The window is valid as long as
 *     window_size - max_count <= k
 * where max_count is the frequency of the most common character in the window
 * (those need not be replaced). When invalid, shrink from the left. We only
 * need max_count to be non-decreasing (we never shrink it) because a larger
 * valid window must have a larger max_count; this keeps the algorithm O(n).
 *
 * Complexity:
 * - Time: O(n)
 * - Space: O(1) — alphabet size is fixed at 26.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> count(26, 0);
        int left = 0;
        int maxCount = 0;   // max frequency of a single char in current window
        int best = 0;

        for (int right = 0; right < (int)s.size(); ++right) {
            int idx = s[right] - 'A';
            count[idx]++;
            maxCount = max(maxCount, count[idx]);

            // Window size = right - left + 1.
            // Characters to replace = windowSize - maxCount.
            // If that exceeds k, shrink window from left.
            while ((right - left + 1) - maxCount > k) {
                count[s[left] - 'A']--;
                left++;
                // Note: we intentionally do NOT recompute maxCount here.
                // A smaller maxCount never helps find a longer window.
            }
            best = max(best, right - left + 1);
        }
        return best;
    }
};

// Optional: quick test
// int main() {
//     Solution s;
//     cout << s.characterReplacement("AABABBA", 1) << endl; // 4
//     return 0;
// }
