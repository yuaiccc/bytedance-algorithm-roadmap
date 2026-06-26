/**
 * LeetCode 1143 - Longest Common Subsequence
 * https://leetcode.com/problems/longest-common-subsequence/
 * Difficulty: Medium
 *
 * Problem:
 * Given two strings text1 and text2, return the length of their longest
 * common subsequence (not necessarily contiguous).
 *
 * Approach:
 * 2D DP. dp[i][j] = LCS length of text1[0..i-1] and text2[0..j-1].
 *   - if text1[i-1] == text2[j-1]: dp[i][j] = dp[i-1][j-1] + 1
 *   - else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 * Base case dp[0][*] = dp[*][0] = 0. Answer = dp[m][n].
 *
 * Complexity:
 * - Time: O(m * n)
 * - Space: O(m * n) (reducible to O(min(m,n)) with a rolling array)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size();
        int n = text2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    cout << sol.longestCommonSubsequence("abcde", "ace") << endl;   // Expected: 3
    cout << sol.longestCommonSubsequence("abc", "abc") << endl;     // Expected: 3
    cout << sol.longestCommonSubsequence("abc", "def") << endl;     // Expected: 0
    return 0;
}
