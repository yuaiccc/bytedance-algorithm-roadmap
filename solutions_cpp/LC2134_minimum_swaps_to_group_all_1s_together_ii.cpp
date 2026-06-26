/**
 * LeetCode 2134 - Minimum Swaps to Group All 1's Together II
 * https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/
 * Difficulty: Medium
 *
 * Problem:
 * A swap is defined as taking two distinct positions in an array and swapping
 * the values in them. A circular array means the end of the array wraps around
 * to the start. Return the minimum number of swaps required to group all 1's
 * present in the array together, in any place, in a circular array.
 *
 * Approach:
 * Let totalOnes = total number of 1's in the array. We want a contiguous
 * window (allowing wrap-around) of size totalOnes that contains as many 1's
 * as possible; the number of swaps needed is totalOnes - (1's in window).
 * Use a fixed-size sliding window of size totalOnes. To handle the circular
 * case, iterate i from 0 to n-1 and treat the window as starting at i; to
 * avoid index arithmetic, double the array conceptually by iterating up to
 * 2*n and using index % n. Track the maximum number of 1's in any window.
 *
 * Complexity:
 * - Time: O(n)
 * - Space: O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = (int)nums.size();
        int totalOnes = 0;
        for (int x : nums) totalOnes += x;
        if (totalOnes == 0 || totalOnes == n) return 0;

        // Count 1's in the first window of size totalOnes.
        int windowOnes = 0;
        for (int i = 0; i < totalOnes; ++i) {
            windowOnes += nums[i];
        }
        int maxOnes = windowOnes;

        // Slide the window around the circular array.
        // Window covers [i - totalOnes + 1, i] (mod n).
        for (int i = totalOnes; i < n + totalOnes; ++i) {
            // Element entering the window.
            windowOnes += nums[i % n];
            // Element leaving the window.
            windowOnes -= nums[(i - totalOnes) % n];
            maxOnes = max(maxOnes, windowOnes);
        }
        // Swaps needed = ones outside the best window = totalOnes - maxOnes.
        return totalOnes - maxOnes;
    }
};

// Optional: quick test
// int main() {
//     Solution s;
//     vector<int> nums = {0, 1, 0, 1, 1, 0, 0};
//     cout << s.minSwaps(nums) << endl; // 1
//     return 0;
// }
