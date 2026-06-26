/**
 * LeetCode 128 - Longest Consecutive Sequence
 * https://leetcode.com/problems/longest-consecutive-sequence/
 * Difficulty: Medium
 *
 * Problem:
 * Given an unsorted array of integers nums, return the length of the longest
 * consecutive elements sequence. The algorithm must run in O(n) time.
 *
 * Approach:
 * Put all numbers into a hash set. For each number, only begin counting a
 * streak if num-1 is NOT in the set — i.e., num is the start of a potential
 * sequence. Then count upwards (num+1, num+2, ...) while the next value is in
 * the set, tracking the maximum streak. The "only start at sequence starts"
 * guard ensures every number is visited at most twice overall, giving O(n).
 *
 * Complexity:
 * - Time: O(n) — each element is part of at most one counting streak.
 * - Space: O(n) — for the hash set.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        int longest = 0;

        for (int num : numSet) {
            // Only start counting from the beginning of a sequence.
            // If num-1 exists, num is not a sequence start, so skip it.
            if (numSet.count(num - 1)) continue;

            int current = num;
            int streak = 1;
            // Extend the streak as long as the next integer exists.
            while (numSet.count(current + 1)) {
                ++current;
                ++streak;
            }
            longest = max(longest, streak);
        }
        return longest;
    }
};

// ---- Local test harness ----
int main() {
    Solution sol;
    vector<int> a = {100, 4, 200, 1, 3, 2};
    cout << sol.longestConsecutive(a) << endl; // 4  (1,2,3,4)

    vector<int> b = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    cout << sol.longestConsecutive(b) << endl; // 9  (0..8)
    return 0;
}
