"""
LeetCode 33 - Search in Rotated Sorted Array
https://leetcode.com/problems/search-in-rotated-sorted-array/

Difficulty: Medium

Problem:
There is an integer array nums sorted in ascending order (with distinct values).
Prior to being passed to the function, nums is possibly rotated at an unknown pivot
index k (1 <= k < nums.length) such that the resulting array is
[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).
Given the array nums after the possible rotation and an integer target, return the
index of target if it is in nums, or -1 if it is not. The algorithm must run in
O(log n) time.

Approach:
Modified binary search. At every step, one of the two halves (left or right of mid)
is guaranteed to be sorted. Determine which half is sorted by comparing nums[mid] with
nums[left]:
- If nums[left] <= nums[mid], the left half is sorted. Check whether target lies
  within [nums[left], nums[mid]) to decide to search left or right.
- Otherwise the right half is sorted. Check whether target lies within
  (nums[mid], nums[right]] to decide to search right or left.
Narrow the search range accordingly until found or the range is empty.

Complexity:
- Time: O(log n), standard binary search halving each iteration
- Space: O(1), only index variables used
"""

from __future__ import annotations

from typing import List


class Solution:
    def search(self, nums: List[int], target: int) -> int:
        left, right = 0, len(nums) - 1

        while left <= right:
            mid = left + (right - left) // 2  # avoid overflow in other languages

            if nums[mid] == target:
                return mid

            # Determine which half is sorted.
            # Left half sorted? (use <= so a single-element range counts as sorted)
            if nums[left] <= nums[mid]:
                # Target is inside the sorted left half
                if nums[left] <= target < nums[mid]:
                    right = mid - 1
                else:
                    left = mid + 1
            else:
                # Right half is sorted
                if nums[mid] < target <= nums[right]:
                    left = mid + 1
                else:
                    right = mid - 1

        return -1


# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------
if __name__ == "__main__":
    sol = Solution()

    # Provided examples
    assert sol.search([4, 5, 6, 7, 0, 1, 2], 0) == 4
    assert sol.search([4, 5, 6, 7, 0, 1, 2], 3) == -1
    assert sol.search([1], 0) == -1

    # Target at boundaries
    assert sol.search([4, 5, 6, 7, 0, 1, 2], 4) == 0
    assert sol.search([4, 5, 6, 7, 0, 1, 2], 2) == 6

    # No rotation (already sorted)
    assert sol.search([1, 2, 3, 4, 5], 3) == 2
    assert sol.search([1, 2, 3, 4, 5], 6) == -1

    # Single element found
    assert sol.search([1], 1) == 0

    # Two elements
    assert sol.search([3, 1], 1) == 1
    assert sol.search([3, 1], 3) == 0
    assert sol.search([1, 3], 3) == 1

    # Rotation at various pivots
    assert sol.search([6, 7, 1, 2, 3, 4, 5], 6) == 0
    assert sol.search([6, 7, 1, 2, 3, 4, 5], 5) == 6
    assert sol.search([2, 4, 5, 6, 7, 0, 1], 0) == 5

    print("All tests passed.")
