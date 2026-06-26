/**
 * LeetCode 221 - Maximal Square
 * https://leetcode.com/problems/maximal-square/
 * Difficulty: Medium
 *
 * Problem:
 * Given an m x n binary matrix filled with '0' and '1', find the area of
 * the largest square containing only '1's.
 *
 * Approach:
 * 2D DP. Let dp[i][j] = side length of the largest square whose bottom-right
 * corner is at (i, j). If matrix[i][j] == '1':
 *     dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1
 * A square ending here is limited by the smallest of the squares ending at
 * the top, left, and top-left neighbors (plus this cell). Track the global
 * max side; return side^2.
 *
 * Complexity:
 * - Time: O(m * n)
 * - Space: O(m * n) (can be reduced to O(n) with a rolling array)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int side = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;  // first row/col can only form side 1
                    } else {
                        dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                    }
                    side = max(side, dp[i][j]);
                }
            }
        }
        return side * side;
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    vector<vector<char>> matrix = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    };
    cout << sol.maximalSquare(matrix) << endl;  // Expected: 4
    return 0;
}
