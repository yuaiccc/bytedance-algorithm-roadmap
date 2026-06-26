/**
 * LeetCode 407 - Trapping Rain Water II
 * https://leetcode.com/problems/trapping-rain-water-ii/
 * Difficulty: Hard
 *
 * Problem:
 * Given an m x n matrix of non-negative heights representing an elevation
 * map, compute the volume of water trapped after raining (water can flow
 * out through the boundary in all 4 directions).
 *
 * Approach:
 * Dijkstra-like expansion from the boundary. Push all boundary cells into a
 * min-heap keyed by height and mark them visited. Repeatedly pop the cell
 * with the smallest effective height `h` (the water level reaching it).
 * For each unvisited neighbor: the water it can hold is max(0, h - height).
 * Then push the neighbor with effective height max(h, neighborHeight) (the
 * water level cannot drop below its own terrain) and mark visited. Because
 * we always expand the lowest boundary, the trapped water at each cell is
 * determined by the minimum-max-height path from the boundary.
 *
 * Complexity:
 * - Time: O(m * n * log(m * n))
 * - Space: O(m * n)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        int n = heightMap[0].size();
        if (m < 3 || n < 3) return 0;

        // min-heap of (effective height, row, col)
        priority_queue<tuple<int, int, int>,
                       vector<tuple<int, int, int>>,
                       greater<tuple<int, int, int>>> pq;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        // Seed the heap with all boundary cells.
        for (int i = 0; i < m; i++) {
            pq.push({heightMap[i][0], i, 0});
            visited[i][0] = true;
            pq.push({heightMap[i][n - 1], i, n - 1});
            visited[i][n - 1] = true;
        }
        for (int j = 1; j < n - 1; j++) {
            pq.push({heightMap[0][j], 0, j});
            visited[0][j] = true;
            pq.push({heightMap[m - 1][j], m - 1, j});
            visited[m - 1][j] = true;
        }

        int water = 0;
        while (!pq.empty()) {
            auto [h, x, y] = pq.top();
            pq.pop();
            for (auto& d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                if (visited[nx][ny]) continue;
                visited[nx][ny] = true;
                if (heightMap[nx][ny] < h) water += h - heightMap[nx][ny];
                pq.push({max(h, heightMap[nx][ny]), nx, ny});
            }
        }
        return water;
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    vector<vector<int>> g1 = {
        {1, 4, 3, 1, 3, 2},
        {3, 2, 1, 3, 2, 4},
        {2, 3, 3, 2, 3, 1}
    };
    cout << sol.trapRainWater(g1) << endl;  // Expected: 4
    return 0;
}
