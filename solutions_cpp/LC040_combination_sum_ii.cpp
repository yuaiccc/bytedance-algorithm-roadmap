/**
 * LeetCode 40 - Combination Sum II
 * https://leetcode.com/problems/combination-sum-ii/
 * Difficulty: Medium
 *
 * Problem:
 * Given a collection of candidate numbers (may contain duplicates) and a
 * target, find all unique combinations that sum to target. Each number may
 * be used at most once (bounded by its frequency). Return unique combos.
 *
 * Approach:
 * Sort the candidates first so duplicates become adjacent. Backtrack while
 * picking candidates at increasing indices. To avoid duplicate combinations,
 * at the same recursion level skip a candidate if it equals the previous
 * candidate that was just considered (i > start && c[i] == c[i-1]). Prune
 * branches where the candidate already exceeds the remaining target.
 *
 * Complexity:
 * - Time: O(2^n) in the worst case.
 * - Space: O(n) recursion stack.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> cur;
        backtrack(candidates, 0, target, cur, res);
        return res;
    }

private:
    void backtrack(const vector<int>& c, int start, int target,
                   vector<int>& cur, vector<vector<int>>& res) {
        if (target == 0) {
            res.push_back(cur);
            return;
        }
        for (int i = start; i < (int)c.size(); i++) {
            if (c[i] > target) break;                  // sorted => prune
            if (i > start && c[i] == c[i - 1]) continue;  // dedup at this level
            cur.push_back(c[i]);
            backtrack(c, i + 1, target - c[i], cur, res);
            cur.pop_back();
        }
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    vector<int> c = {10, 1, 2, 7, 6, 1, 5};
    auto res = sol.combinationSum2(c, 8);
    for (auto& combo : res) {
        cout << "[";
        for (int i = 0; i < (int)combo.size(); i++) cout << combo[i] << (i + 1 < (int)combo.size() ? "," : "");
        cout << "]" << endl;
    }
    return 0;
}
