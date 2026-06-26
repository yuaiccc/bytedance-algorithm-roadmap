"""
LeetCode 56 - Merge Intervals
https://leetcode.com/problems/merge-intervals/

Difficulty: Medium

Problem:
Given an array of `intervals` where intervals[i] = [start_i, end_i], merge all
overlapping intervals, and return an array of the non-overlapping intervals that
cover all the intervals in the input.

Approach (Sort + Linear Scan):
1. Sort the intervals by their start time. After sorting, any overlapping
   intervals will be adjacent (or chained through neighbors), so we can merge
   in a single left-to-right pass.
2. Initialize a `merged` list with the first interval.
3. For each subsequent interval [start, end]:
   - If start <= last_merged_end: the intervals overlap. Merge by updating the
     end of the last interval in `merged` to max(last_merged_end, end).
   - Else: no overlap; append the interval as a new entry.

Why sorting by start works:
After sorting, interval i's start <= interval (i+1)'s start. If they overlap
(start_{i+1} <= end_i), merging them produces [start_i, max(end_i, end_{i+1})].
If they don't overlap, interval i+1 and all later intervals have start >= start_{i+1}
> end_i, so interval i cannot overlap anything later either -- we can safely
move on.

Complexity:
- Time: O(n log n) dominated by the sort; the linear scan is O(n).
- Space: O(n) for the output list (O(log n) extra for the sort's stack if we
  don't count the output).
"""

from typing import List


class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        if not intervals:
            return []

        # Step 1: sort by start time.
        intervals.sort(key=lambda x: x[0])

        merged = [intervals[0]]  # seed with the first interval

        for start, end in intervals[1:]:
            last_end = merged[-1][1]
            if start <= last_end:
                # Overlapping intervals -> merge by extending the end.
                merged[-1][1] = max(last_end, end)
            else:
                # Disjoint interval -> append as a new entry.
                merged.append([start, end])

        return merged


# ---------------------------------------------------------------------------
# Example usage / quick test
# ---------------------------------------------------------------------------
if __name__ == "__main__":
    sol = Solution()
    print(sol.merge([[1, 3], [2, 6], [8, 10], [15, 18]]))
    # [[1, 6], [8, 10], [15, 18]]
    print(sol.merge([[1, 4], [4, 5]]))   # [[1, 5]]
    print(sol.merge([[1, 4], [0, 4]]))   # [[0, 4]]  (sort handles out-of-order)
