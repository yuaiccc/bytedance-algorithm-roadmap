"""
LeetCode 200 - Number of Islands
https://leetcode.com/problems/number-of-islands/

Difficulty: Medium

Problem:
Given an m x n 2D binary grid which represents a map of '1's (land) and '0's (water),
return the number of islands. An island is surrounded by water and is formed by
connecting adjacent lands horizontally or vertically. You may assume all four edges
of the grid are all surrounded by water.

Approach:
Use DFS flood fill. Iterate over every cell in the grid. When we encounter an
unvisited land cell ('1'), we increment the island count and perform a DFS to mark
all connected land cells (up/down/left/right) as visited. We mark visited cells
in-place by overwriting '1' with '0' (sinking the island), which avoids needing an
extra visited matrix. Each cell is processed at most once during DFS, so the whole
grid is scanned in a single pass.

Complexity:
- Time: O(M * N) where M is the number of rows and N is the number of columns.
  Each cell is visited once by the outer loop and once by DFS at most.
- Space: O(M * N) in the worst case for the recursion stack (a grid filled with
  land). In the average case it is much smaller. BFS would use O(min(M, N)).
"""

from typing import List


class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        """Count islands in a 2D grid using DFS flood fill."""
        if not grid or not grid[0]:
            return 0

        rows, cols = len(grid), len(grid[0])
        island_count = 0

        def dfs(r: int, c: int) -> None:
            """Mark the entire connected land component starting at (r, c) as visited."""
            # Boundary and water checks: stop DFS if out of bounds or on water
            if r < 0 or r >= rows or c < 0 or c >= cols:
                return
            if grid[r][c] != '1':
                return

            # Sink this land cell so we don't revisit it
            grid[r][c] = '0'

            # Explore all four directions
            dfs(r - 1, c)  # up
            dfs(r + 1, c)  # down
            dfs(r, c - 1)  # left
            dfs(r, c + 1)  # right

        for i in range(rows):
            for j in range(cols):
                # Found a new island: count it and flood-fill all its cells
                if grid[i][j] == '1':
                    island_count += 1
                    dfs(i, j)

        return island_count


# --------------------- Alternative: iterative DFS (no recursion) ---------------------
class SolutionIterative:
    def numIslands(self, grid: List[List[str]]) -> int:
        """Iterative DFS using an explicit stack to avoid recursion limits."""
        if not grid or not grid[0]:
            return 0

        rows, cols = len(grid), len(grid[0])
        island_count = 0
        directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

        for i in range(rows):
            for j in range(cols):
                if grid[i][j] == '1':
                    island_count += 1
                    stack = [(i, j)]
                    grid[i][j] = '0'  # mark visited
                    while stack:
                        r, c = stack.pop()
                        for dr, dc in directions:
                            nr, nc = r + dr, c + dc
                            if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == '1':
                                grid[nr][nc] = '0'
                                stack.append((nr, nc))

        return island_count


if __name__ == "__main__":
    # Simple smoke test
    grid = [
        ["1", "1", "0", "0", "0"],
        ["1", "1", "0", "0", "0"],
        ["0", "0", "1", "0", "0"],
        ["0", "0", "0", "1", "1"],
    ]
    print(Solution().numIslands(grid))  # Expected: 3
