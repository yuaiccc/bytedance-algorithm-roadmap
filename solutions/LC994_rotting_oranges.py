"""
LeetCode 994 - Rotting Oranges
https://leetcode.com/problems/rotting-oranges/

Difficulty: Medium

Problem:
You are given an m x n grid where each cell can have one of three values:
    0 - empty cell
    1 - fresh orange
    2 - rotten orange
Every minute, any fresh orange that is 4-directionally adjacent to a rotten
orange becomes rotten. Return the minimum number of minutes that must elapse
until no cell has a fresh orange. If this is impossible, return -1.

Approach:
This is a multi-source shortest-path / level-order BFS problem. All initially
rotten oranges begin rotting their neighbors simultaneously, so we start BFS
from ALL rotten oranges at once (rather than a single source).

Steps:
1. Scan the grid: enqueue every rotten orange, count fresh oranges.
2. If there are no fresh oranges, return 0 immediately (already done).
3. Run BFS level by level. Each level = one minute. For every rotten orange
   dequeued, rot its fresh 4-directional neighbors, enqueue them, and decrement
   the fresh counter.
4. After BFS, if fresh == 0 return the elapsed minutes; otherwise return -1
   (some fresh orange was unreachable).

Complexity:
- Time: O(M * N) -- every cell is enqueued/dequeued at most once.
- Space: O(M * N) in the worst case for the queue (e.g. all cells rotten).
"""

from typing import List
from collections import deque


class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        """Return minutes until all oranges rot, or -1 if impossible."""
        if not grid or not grid[0]:
            return -1

        rows, cols = len(grid), len(grid[0])
        queue = deque()
        fresh_count = 0

        # Step 1: locate all initially rotten oranges and count fresh ones.
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 2:
                    queue.append((r, c))
                elif grid[r][c] == 1:
                    fresh_count += 1

        # No fresh oranges to rot -> 0 minutes needed.
        if fresh_count == 0:
            return 0

        minutes = 0
        directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]

        # Step 2 & 3: BFS level by level; each level is one minute.
        while queue and fresh_count > 0:
            # Process all rotten oranges that exist at the start of this minute.
            for _ in range(len(queue)):
                r, c = queue.popleft()
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    # Only rot fresh, in-bounds oranges.
                    if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == 1:
                        grid[nr][nc] = 2          # mark as rotten
                        fresh_count -= 1          # one fewer fresh orange
                        queue.append((nr, nc))    # will rot others next minute
            minutes += 1

        # Step 4: if any fresh orange remains, it was unreachable -> -1.
        return minutes if fresh_count == 0 else -1


if __name__ == "__main__":
    sol = Solution()
    print(sol.orangesRotting([[2, 1, 1], [1, 1, 0], [0, 1, 1]]))  # 4
    print(sol.orangesRotting([[2, 1, 1], [0, 1, 1], [1, 0, 1]]))  # -1
    print(sol.orangesRotting([[0, 2]]))                            # 0
