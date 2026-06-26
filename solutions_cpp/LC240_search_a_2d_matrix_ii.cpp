/**
 * LeetCode 240 - Search a 2D Matrix II
 * https://leetcode.com/problems/search-a-2d-matrix-ii/
 * Difficulty: Medium
 *
 * Problem:
 * Given an m x n matrix where each row and each column is sorted in ascending
 * order (left to right and top to bottom), write an efficient algorithm that
 * returns true if the target value exists in the matrix.
 *
 * Approach:
 * Start from the top-right corner. At each cell (row, col):
 *   - If matrix[row][col] == target, found it.
 *   - If matrix[row][col] > target, the entire column below is also larger, so
 *     move left (col--).
 *   - If matrix[row][col] < target, the entire row to the left is smaller, so
 *     move down (row++).
 * Each comparison eliminates one row or one column, giving O(m + n) time.
 *
 * Complexity:
 * - Time: O(m + n) — at most m row-steps + n col-steps.
 * - Space: O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        int m = (int)matrix.size();
        int n = (int)matrix[0].size();

        int row = 0;
        int col = n - 1; // start at top-right corner

        while (row < m && col >= 0) {
            int val = matrix[row][col];
            if (val == target) {
                return true;
            } else if (val > target) {
                --col; // this column is too large, go left
            } else {
                ++row; // this row is too small, go down
            }
        }
        return false;
    }
};

// ---- Local test harness ----
int main() {
    Solution sol;
    vector<vector<int>> matrix = {
        {1, 4, 7, 11, 15},
        {2, 5, 8, 12, 19},
        {3, 6, 9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };
    cout << boolalpha;
    cout << sol.searchMatrix(matrix, 5) << endl;  // true
    cout << sol.searchMatrix(matrix, 20) << endl; // false
    return 0;
}
