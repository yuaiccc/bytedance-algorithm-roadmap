/**
 * LeetCode 560 - Subarray Sum Equals K
 * https://leetcode.com/problems/subarray-sum-equals-k/
 * Difficulty: Medium
 *
 * Problem:
 * Given an array of integers nums and an integer k, return the total number of
 * subarrays whose sum equals k. A subarray is a contiguous non-empty portion of
 * the array.
 *
 * Approach:
 * Use prefix sums. Let prefix[i] = sum of nums[0..i-1]. The sum of subarray
 * nums[i..j-1] equals prefix[j] - prefix[i]. We want prefix[j] - prefix[i] == k,
 * i.e. prefix[i] == prefix[j] - k. As we iterate, maintain a hash map counting
 * how many times each prefix sum has occurred so far. For the current prefix
 * sum `cur`, add count[cur - k] to the answer, then record `cur` in the map.
 * Initialize the map with {0: 1} to handle subarrays starting at index 0.
 *
 * Complexity:
 * - Time: O(n)
 * - Space: O(n)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefixCount;
        prefixCount[0] = 1; // empty prefix sum occurs once
        int cur = 0;
        int ans = 0;
        for (int x : nums) {
            cur += x;
            // Look for a previous prefix sum equal to cur - k.
            auto it = prefixCount.find(cur - k);
            if (it != prefixCount.end()) {
                ans += it->second;
            }
            prefixCount[cur]++;
        }
        return ans;
    }
};

// Optional: quick test
// int main() {
//     Solution s;
//     vector<int> nums = {1, 1, 1};
//     cout << s.subarraySum(nums, 2) << endl; // 2
//     return 0;
// }
