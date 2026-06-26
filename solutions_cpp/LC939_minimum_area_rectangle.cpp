/**
 * LeetCode 939 - Minimum Area Rectangle
 * https://leetcode.com/problems/minimum-area-rectangle/
 * Difficulty: Medium
 *
 * Problem:
 * You are given an array of points in the X-Y plane points where points[i] =
 * [xi, yi]. Return the minimum area of a rectangle formed from these points,
 * with sides parallel to the X and Y axes. If there is no such rectangle,
 * return 0.
 *
 * Approach:
 * A rectangle (axis-aligned) is uniquely determined by a pair of diagonal
 * points (x1, y1) and (x2, y2) with x1 != x2 and y1 != y2. The other two
 * corners are (x1, y2) and (x2, y1). If both of those exist in our point set,
 * we have a valid rectangle of area |x2-x1| * |y2-y1|. Store all points in a
 * hash set (encoded as integers) for O(1) existence checks, then enumerate all
 * pairs of points as candidate diagonals.
 *
 * Complexity:
 * - Time: O(n^2) — enumerate all pairs of points.
 * - Space: O(n) — hash set of points.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        // Encode each point (x, y) into a single 64-bit integer for hashing.
        // x, y in [0, 40000] so 16 bits each is enough; use shifts to be safe.
        unordered_set<long long> pointSet;
        for (auto& p : points) {
            pointSet.insert(encode(p[0], p[1]));
        }

        int best = INT_MAX;
        int n = (int)points.size();
        // Enumerate every pair as a potential diagonal.
        for (int i = 0; i < n; ++i) {
            int x1 = points[i][0], y1 = points[i][1];
            for (int j = i + 1; j < n; ++j) {
                int x2 = points[j][0], y2 = points[j][1];
                // Diagonal requires different x and different y.
                if (x1 != x2 && y1 != y2) {
                    // Check the other two corners exist.
                    if (pointSet.count(encode(x1, y2)) &&
                        pointSet.count(encode(x2, y1))) {
                        int area = abs(x2 - x1) * abs(y2 - y1);
                        best = min(best, area);
                    }
                }
            }
        }
        return best == INT_MAX ? 0 : best;
    }

private:
    static long long encode(int x, int y) {
        // Combine x and y into a single 64-bit key.
        return ((long long)x << 32) | (long long)(unsigned int)y;
    }
};

// Optional: quick test
// int main() {
//     Solution s;
//     vector<vector<int>> points = {{1,1},{1,3},{3,1},{3,3},{2,2}};
//     cout << s.minAreaRect(points) << endl; // 4
//     return 0;
// }
