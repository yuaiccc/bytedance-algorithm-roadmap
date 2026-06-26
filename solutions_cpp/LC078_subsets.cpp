/**
 * LeetCode 78 - Subsets
 * https://leetcode.com/problems/subsets/
 * Difficulty: Medium
 *
 * Problem:
 * Given an integer array of unique elements, return all possible subsets
 * (the power set). The solution set must not contain duplicate subsets.
 *
 * Approach:
 * Classic backtracking. For each position we choose to either include the
 * current element or skip it. Equivalently, iterate over candidate next
 * elements starting from `start`, push one, recurse with i+1, then pop.
 * Every node of the recursion tree (including the empty set) is recorded.
 *
 * Complexity:
 * - Time: O(n * 2^n)  — 2^n subsets, each copied in O(n).
 * - Space: O(n) recursion stack (excluding output).
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> cur;
        backtrack(nums, 0, cur, res);
        return res;
    }

private:
    void backtrack(const vector<int>& nums, int start,
                   vector<int>& cur, vector<vector<int>>& res) {
        res.push_back(cur);  // record the current subset
        for (int i = start; i < (int)nums.size(); i++) {
            cur.push_back(nums[i]);           // choose nums[i]
            backtrack(nums, i + 1, cur, res); // recurse
            cur.pop_back();                   // undo choice
        }
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3};
    auto res = sol.subsets(nums);
    for (auto& s : res) {
        cout << "[";
        for (int i = 0; i < (int)s.size(); i++) cout << s[i] << (i + 1 < (int)s.size() ? "," : "");
        cout << "]" << endl;
    }
    return 0;
}
