/**
 * LeetCode 55 - Jump Game
 * https://leetcode.com/problems/jump-game/
 * Difficulty: Medium
 *
 * Problem:
 * You start at index 0 of a non-negative array `nums` where nums[i] is the
 * max jump length from i. Return true if you can reach the last index.
 *
 * Approach:
 * Greedy. Keep the farthest index reachable so far (`maxReach`). Iterate
 * left to right; if the current index ever exceeds maxReach, we are stuck
 * and return false. Otherwise extend maxReach = max(maxReach, i + nums[i]).
 * If we finish the loop (maxReach >= last index), return true.
 *
 * Complexity:
 * - Time: O(n)
 * - Space: O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int maxReach = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (i > maxReach) return false;       // cannot reach index i
            maxReach = max(maxReach, i + nums[i]);
            if (maxReach >= n - 1) return true;   // early exit
        }
        return true;
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    vector<int> a = {2, 3, 1, 1, 4};
    cout << sol.canJump(a) << endl;  // Expected: 1 (true)

    vector<int> b = {3, 2, 1, 0, 4};
    cout << sol.canJump(b) << endl;  // Expected: 0 (false)
    return 0;
}
