/**
 * LeetCode 317 - Shortest Distance from All Buildings
 * https://leetcode.com/problems/shortest-distance-from-all-buildings/
 * Difficulty: Hard
 *
 * Problem:
 * Given a grid of values 0 (empty land), 1 (building), 2 (obstacle),
 * find an empty land cell that has the shortest total Manhattan distance
 * to all buildings and is reachable from every building. Return that
 * minimum total distance, or -1 if no such cell exists.
 *
 * Approach:
 * Run a multi-source BFS from each building (grid value 1). Maintain two
 * auxiliary grids: `dist` accumulates the total distance from every
 * building to each empty cell, and `reach` counts how many buildings can
 * reach each empty cell. Only expand BFS through empty land cells (0),
 * treating buildings and obstacles as walls. After processing all
 * buildings, scan for empty cells whose reach count equals the total
 * number of buildings and pick the minimum accumulated distance.
 *
 * Complexity:
 * - Time: O(B * m * n) where B is the number of buildings. In the worst
 *   case B = O(m*n), giving O(m^2 * n^2).
 * - Space: O(m * n) for the distance, reach and visited grids.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dist(m, vector<int>(n, 0));   // total distance to all buildings
        vector<vector<int>> reach(m, vector<int>(n, 0));  // #buildings that can reach this cell

        int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int buildings = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != 1) continue;

                buildings++;
                // BFS from this building over empty land only.
                queue<pair<int, int>> q;
                q.push({i, j});
                vector<vector<bool>> visited(m, vector<bool>(n, false));
                visited[i][j] = true;

                int level = 0;
                while (!q.empty()) {
                    int sz = q.size();
                    level++;  // distance of the next layer
                    while (sz--) {
                        auto [x, y] = q.front();
                        q.pop();
                        for (auto& d : dirs) {
                            int nx = x + d[0], ny = y + d[1];
                            if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                            if (visited[nx][ny] || grid[nx][ny] != 0) continue;
                            visited[nx][ny] = true;
                            dist[nx][ny] += level;
                            reach[nx][ny]++;
                            q.push({nx, ny});
                        }
                    }
                }
            }
        }

        int ans = INT_MAX;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0 && reach[i][j] == buildings) {
                    ans = min(ans, dist[i][j]);
                }
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    vector<vector<int>> grid1 = {
        {1, 0, 2, 0, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0}
    };
    cout << sol.shortestDistance(grid1) << endl;  // Expected: 7

    vector<vector<int>> grid2 = {
        {1, 0},
        {0, 0}
    };
    cout << sol.shortestDistance(grid2) << endl;  // Expected: 1
    return 0;
}
