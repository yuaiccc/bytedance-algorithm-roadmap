/**
 * LeetCode 70 - Climbing Stairs
 * https://leetcode.com/problems/climbing-stairs/
 * Difficulty: Easy
 *
 * Problem:
 * You are climbing a staircase. It takes n steps to reach the top. Each time
 * you can either climb 1 or 2 steps. In how many distinct ways can you climb
 * to the top?
 *
 * Approach:
 * This is the Fibonacci recurrence: ways(n) = ways(n-1) + ways(n-2), because
 * the last move is either 1 step (from n-1) or 2 steps (from n-2). Base cases:
 * ways(1) = 1, ways(2) = 2. We use rolling variables (prev2, prev1) instead of
 * a full DP array to achieve O(1) space.
 *
 * Complexity:
 * - Time: O(n)
 * - Space: O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        // prev2 = ways(i-2), prev1 = ways(i-1)
        int prev2 = 1; // ways(1)
        int prev1 = 2; // ways(2)
        for (int i = 3; i <= n; ++i) {
            int cur = prev1 + prev2;
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;
    }
};

// Optional: quick test
// int main() {
//     Solution s;
//     cout << s.climbStairs(5) << endl; // 8
//     return 0;
// }
