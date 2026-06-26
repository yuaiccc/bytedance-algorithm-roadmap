/**
 * LeetCode 213 - House Robber II
 * https://leetcode.com/problems/house-robber-ii/
 * Difficulty: Medium
 *
 * Problem:
 * Same as House Robber, but the houses are arranged in a circle (first and
 * last are adjacent). You cannot rob two adjacent houses. Return the max.
 *
 * Approach:
 * Because house 0 and house n-1 are now adjacent, you can rob at most one
 * of them. Split into two linear cases and take the max:
 *   (1) rob houses in [0, n-2]  (exclude the last house), or
 *   (2) rob houses in [1, n-1]  (exclude the first house).
 * Each case reduces to the linear House Robber (LC198). Edge case: n == 1.
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
        int n = nums.size();
        if (n == 1) return nums[0];
        // Either skip the last house or skip the first house.
        return max(robRange(nums, 0, n - 2), robRange(nums, 1, n - 1));
    }

private:
    int robRange(vector<int>& nums, int l, int r) {
        int prev2 = 0, prev1 = 0;
        for (int i = l; i <= r; i++) {
            int cur = max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    vector<int> a = {2, 3, 2};
    cout << sol.rob(a) << endl;  // Expected: 3

    vector<int> b = {1, 2, 3, 1};
    cout << sol.rob(b) << endl;  // Expected: 4

    vector<int> c = {1};
    cout << sol.rob(c) << endl;  // Expected: 1
    return 0;
}
