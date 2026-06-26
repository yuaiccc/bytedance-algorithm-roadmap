/**
 * LeetCode 347 - Top K Frequent Elements
 * https://leetcode.com/problems/top-k-frequent-elements/
 * Difficulty: Medium
 *
 * Problem:
 * Given an integer array and an integer k, return the k most frequent
 * elements. The answer is guaranteed to be unique (any valid order ok).
 *
 * Approach:
 * Bucket sort. Count frequencies with a hash map, then place each number
 * into a bucket indexed by its frequency (bucket size = n + 1, since a
 * number can appear at most n times). Iterate buckets from high frequency
 * to low, collecting numbers until we have k. This avoids the O(n log k)
 * heap and achieves linear time.
 *
 * Complexity:
 * - Time: O(n) average
 * - Space: O(n)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        for (int x : nums) cnt[x]++;

        int n = nums.size();
        vector<vector<int>> bucket(n + 1);  // bucket[f] = numbers with frequency f
        for (auto& [num, f] : cnt) bucket[f].push_back(num);

        vector<int> res;
        for (int f = n; f >= 0 && (int)res.size() < k; f--) {
            for (int num : bucket[f]) {
                res.push_back(num);
                if ((int)res.size() == k) break;
            }
        }
        return res;
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    vector<int> a = {1, 1, 1, 2, 2, 3};
    auto r1 = sol.topKFrequent(a, 2);
    for (int x : r1) cout << x << " ";  // 1 2
    cout << endl;

    vector<int> b = {1};
    auto r2 = sol.topKFrequent(b, 1);
    for (int x : r2) cout << x << " ";  // 1
    cout << endl;
    return 0;
}
