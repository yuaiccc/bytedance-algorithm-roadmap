/**
 * LeetCode 10 - Regular Expression Matching
 * https://leetcode.com/problems/regular-expression-matching/
 * Difficulty: Hard
 *
 * Problem:
 * Implement '.' (matches any single char) and '*' (matches zero or more of
 * the preceding element) matching. Given string s and pattern p, return
 * true if the entire string matches the pattern.
 *
 * Approach:
 * 2D DP. dp[i][j] = whether s[0..i-1] matches p[0..j-1].
 *   - dp[0][0] = true.
 *   - For empty s, a '*' can erase its preceding element:
 *         if p[j-1] == '*': dp[0][j] = dp[0][j-2].
 *   - If p[j-1] == '*':
 *        zero of preceding element: dp[i][j] = dp[i][j-2];
 *        one-or-more: if preceding (p[j-2]) matches s[i-1] (equal or '.'),
 *            dp[i][j] |= dp[i-1][j].
 *   - Else (literal or '.'): if p[j-1] matches s[i-1], dp[i][j] = dp[i-1][j-1].
 *
 * Complexity:
 * - Time: O(m * n)
 * - Space: O(m * n)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;

        // Pattern matches empty string via "x*" erasures.
        for (int j = 2; j <= n; j++) {
            if (p[j - 1] == '*') dp[0][j] = dp[0][j - 2];
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] == '*') {
                    // match zero occurrences of the preceding element
                    dp[i][j] = dp[i][j - 2];
                    // match one-or-more if preceding element matches s[i-1]
                    if (p[j - 2] == s[i - 1] || p[j - 2] == '.') {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                } else {
                    if (p[j - 1] == s[i - 1] || p[j - 1] == '.') {
                        dp[i][j] = dp[i - 1][j - 1];
                    }
                }
            }
        }
        return dp[m][n];
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    cout << sol.isMatch("aa", "a") << endl;       // 0
    cout << sol.isMatch("aa", "a*") << endl;      // 1
    cout << sol.isMatch("ab", ".*") << endl;      // 1
    cout << sol.isMatch("aab", "c*a*b") << endl;  // 1
    cout << sol.isMatch("mississippi", "mis*is*p*.") << endl;  // 0
    return 0;
}
