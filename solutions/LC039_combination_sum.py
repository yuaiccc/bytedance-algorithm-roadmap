"""
LeetCode 39 - Combination Sum
https://leetcode.com/problems/combination-sum/

Difficulty: Medium

Problem:
Given an array of distinct integers `candidates` and a target integer `target`,
return a list of all unique combinations of `candidates` where the chosen numbers
sum to `target`. The same number may be chosen from `candidates` an unlimited number
of times. Two combinations are unique if the frequency of at least one chosen number
is different.

Approach:
Use backtracking (DFS). At each step we either:
  1. Pick the candidate at the current index (stay at the same index since reuse is allowed),
     subtracting its value from the remaining target, OR
  2. Skip it and move to the next index (to avoid duplicate combinations).

The key insight for avoiding duplicates is to enforce a non-decreasing index order:
once we move past an index we never come back to it. This way we naturally avoid
generating permutations of the same combination (e.g. [2,3] and [3,2]).

Pruning: if we sort candidates first, we can break early once the current candidate
exceeds the remaining target, since all subsequent candidates are larger.

Complexity:
- Time: O(N^(T/M+1)) where N = number of candidates, T = target, M = min candidate.
        In the worst case the recursion tree depth is T/M (all smallest candidates).
- Space: O(T/M) for the recursion stack depth (plus output storage).
"""

from typing import List


class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        result = []
        # Sort to enable pruning: once a candidate exceeds remaining target,
        # all larger candidates will too, so we can break immediately.
        candidates.sort()
        self._backtrack(candidates, target, start=0, path=[], result=result)
        return result

    def _backtrack(
        self,
        candidates: List[int],
        remaining: int,
        start: int,
        path: List[int],
        result: List[List[int]],
    ) -> None:
        # Base case: we hit the target exactly.
        if remaining == 0:
            # Append a copy of the current path.
            result.append(path[:])
            return

        for i in range(start, len(candidates)):
            candidate = candidates[i]
            # Pruning: since candidates are sorted, no later candidate can work either.
            if candidate > remaining:
                break

            # Choose: include candidates[i] in the current combination.
            path.append(candidate)
            # Explore: stay at index i because the same element can be reused.
            self._backtrack(candidates, remaining - candidate, i, path, result)
            # Un-choose (backtrack): remove the last element to try next candidate.
            path.pop()


# ---------------------------------------------------------------------------
# Example usage / quick test
# ---------------------------------------------------------------------------
if __name__ == "__main__":
    sol = Solution()
    print(sol.combinationSum([2, 3, 6, 7], 7))   # [[2, 2, 3], [7]]
    print(sol.combinationSum([2, 3, 5], 8))        # [[2,2,2,2],[2,3,3],[3,5]]
    print(sol.combinationSum([2], 1))              # []
