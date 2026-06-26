/**
 * LeetCode 1 - Two Sum
 * https://leetcode.com/problems/two-sum/
 * Difficulty: Easy
 *
 * Problem:
 * Given an array of integers nums and an integer target, return indices of the
 * two numbers such that they add up to target. You may assume that each input
 * would have exactly one solution, and you may not use the same element twice.
 * The answer can be returned in any order.
 *
 * Approach:
 * Use a hash map to store each number's value -> index mapping in a single pass.
 * For every element nums[i], compute complement = target - nums[i]. If the
 * complement already exists in the map, we have found the pair and return both
 * indices. Otherwise, insert the current number into the map and continue.
 * One-pass ensures we never reuse the same element.
 *
 * Complexity:
 * - Time: O(n) — single pass over the array, each lookup/insert is O(1) average.
 * - Space: O(n) — hash map stores up to n entries.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // value -> index
        unordered_map<int, int> seen;
        for (int i = 0; i < (int)nums.size(); ++i) {
            int complement = target - nums[i];
            auto it = seen.find(complement);
            if (it != seen.end()) {
                // Found the pair; return earlier index first.
                return {it->second, i};
            }
            seen[nums[i]] = i;
        }
        // Per problem statement a solution always exists.
        return {};
    }
};

// Optional: quick test
// int main() {
//     Solution s;
//     vector<int> nums = {2, 7, 11, 15};
//     auto r = s.twoSum(nums, 9);
//     cout << r[0] << " " << r[1] << endl; // 0 1
//     return 0;
// }
