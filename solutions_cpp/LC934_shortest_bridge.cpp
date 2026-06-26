/**
 * LeetCode 934 - Shortest Bridge
 * https://leetcode.com/problems/shortest-bridge/
 * Difficulty: Medium
 *
 * Problem:
 * Given an n x n binary matrix grid where there are exactly two islands
 * (4-directionally connected groups of 1s), return the smallest number of 0s
 * that must be flipped to 1 to connect the two islands into one.
 *
 * Approach:
 * 1) Find the first island: scan the grid for the first 1, then DFS to mark
 *    every cell of that island as 2 and enqueue all its cells into a BFS queue.
 * 2) Multi-source BFS: expand outward layer by layer from every cell of the
 *    first island. The moment BFS reaches a cell with value 1 (the second
 *    island), the number of expansion layers taken is the answer (the number
 *    of 0s crossed). Mark visited water cells as 2 to avoid revisiting.
 *
 * Complexity:
 * - Time: O(n^2) — each cell is processed a constant number of times.
 * - Space: O(n^2) — for the BFS queue in the worst case.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    static constexpr int DIRS[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int n;

    // DFS to paint the first island (mark as 2) and seed the BFS queue.
    void dfs(vector<vector<int>>& grid, int r, int c, queue<pair<int, int>>& q) {
        if (r < 0 || r >= n || c < 0 || c >= n || grid[r][c] != 1) return;
        grid[r][c] = 2;       // mark visited / part of first island
        q.push({r, c});       // seed BFS with this cell
        for (auto& d : DIRS) {
            dfs(grid, r + d[0], c + d[1], q);
        }
    }

public:
    int shortestBridge(vector<vector<int>>& grid) {
        n = (int)grid.size();
        queue<pair<int, int>> q;

        // Step 1: locate and paint the first island, filling the queue.
        bool found = false;
        for (int i = 0; i < n && !found; ++i) {
            for (int j = 0; j < n && !found; ++j) {
                if (grid[i][j] == 1) {
                    dfs(grid, i, j, q);
                    found = true;
                }
            }
        }

        // Step 2: multi-source BFS outward until we hit the second island.
        int steps = 0;
        while (!q.empty()) {
            int size = (int)q.size();
            while (size--) {
                auto [r, c] = q.front(); q.pop();
                for (auto& d : DIRS) {
                    int nr = r + d[0];
                    int nc = c + d[1];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                    if (grid[nr][nc] == 1) return steps; // reached second island
                    if (grid[nr][nc] == 0) {              // expand into water
                        grid[nr][nc] = 2;                 // mark visited
                        q.push({nr, nc});
                    }
                }
            }
            ++steps; // finished one BFS layer
        }
        return -1; // should never happen (two islands are guaranteed)
    }
};

// ---- Local test harness ----
int main() {
    Solution sol;
    vector<vector<int>> g1 = {
        {0, 1},
        {1, 0}
    };
    cout << sol.shortestBridge(g1) << endl; // 1

    vector<vector<int>> g2 = {
        {0, 1, 0},
        {0, 0, 0},
        {0, 0, 1}
    };
    cout << sol.shortestBridge(g2) << endl; // 2

    vector<vector<int>> g3 = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };
    cout << sol.shortestBridge(g3) << endl; // 1
    return 0;
}
