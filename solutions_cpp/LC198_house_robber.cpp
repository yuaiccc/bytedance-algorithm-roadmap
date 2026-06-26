/**
 * LeetCode 198 - House Robber
 * https://leetcode.com/problems/house-robber/
 * Difficulty: Easy
 *
 * Problem:
 * You are a robber planning to rob houses along a street, each with some
 * money. You cannot rob two adjacent houses. Return the maximum amount you
 * can rob.
 *
 * Approach:
 * Linear DP. Let dp[i] = max money robbable from houses 0..i. Then
 *     dp[i] = max(dp[i-1], dp[i-2] + nums[i])
 * (skip house i, or rob it and add dp[i-2]). We only need the last two
 * values, so roll them into two variables for O(1) space.
 *
 * Complexity:
 * - Time: O(n)
 * - Space: O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int prev2 = 0;  // dp[i-2]
        int prev1 = 0;  // dp[i-1]
        for (int x : nums) {
            int cur = max(prev1, prev2 + x);
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    vector<int> a = {1, 2, 3, 1};
    cout << sol.rob(a) << endl;  // Expected: 4

    vector<int> b = {2, 7, 9, 3, 1};
    cout << sol.rob(b) << endl;  // Expected: 12
    return 0;
}
