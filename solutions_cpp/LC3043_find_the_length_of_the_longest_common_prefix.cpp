/**
 * LeetCode 3043 - Find the Length of the Longest Common Prefix
 * https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/
 * Difficulty: Medium
 *
 * Problem:
 * Given two arrays of positive integers arr1 and arr2, return the length
 * of the longest common prefix shared by any integer in arr1 and any
 * integer in arr2.
 *
 * Approach:
 * Insert every numeric prefix of every number in arr1 into a hash set (a
 * prefix is obtained by repeatedly removing the last digit). For each
 * number in arr2, walk down its prefixes from longest to shortest; the
 * first prefix found in the set gives that number's best match, and its
 * digit count is a candidate answer. Track the global max. Numeric prefixes
 * equal sharing the same leading digits, so the matched prefix's digit
 * count equals the common-prefix length.
 *
 * Complexity:
 * - Time: O((N1 + N2) * d) where d is the max number of digits (~9).
 * - Space: O(N1 * d)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        unordered_set<int> prefixes;
        for (int x : arr1) {
            while (x > 0) {
                prefixes.insert(x);
                x /= 10;  // chop last digit -> shorter prefix
            }
        }

        int ans = 0;
        for (int x : arr2) {
            int len = (int)to_string(x).size();
            int cur = x;
            while (cur > 0) {
                if (prefixes.count(cur)) {
                    ans = max(ans, len);
                    break;  // longest match for this number found
                }
                cur /= 10;
                len--;
            }
        }
        return ans;
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    vector<int> a1 = {1, 10, 100};
    vector<int> a2 = {1000};
    cout << sol.longestCommonPrefix(a1, a2) << endl;  // Expected: 3

    vector<int> b1 = {1, 2, 3};
    vector<int> b2 = {4, 4, 4};
    cout << sol.longestCommonPrefix(b1, b2) << endl;  // Expected: 0
    return 0;
}
