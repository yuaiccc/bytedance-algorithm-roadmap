"""
LeetCode 215 - Kth Largest Element in an Array
https://leetcode.com/problems/kth-largest-element-in-an-array/

Difficulty: Medium

Problem:
Given an integer array nums and an integer k, return the k-th largest element
in the array. Note that it is the k-th largest element in the sorted order,
not the k-th distinct element. You must solve it without sorting the full array.

Example:
    Input:  nums = [3,2,1,5,6,4], k = 2
    Output: 5   (sorted descending: [6,5,4,3,2,1], 2nd largest is 5)

Approach:
We provide two solutions:

1) Min-heap of size k (heapq):
   Maintain a min-heap that always holds the k largest elements seen so far.
   Iterate through nums: push each element; if the heap exceeds size k, pop the
   smallest. At the end, the root of the min-heap is the k-th largest element.
   Intuition: a min-heap of the k biggest values keeps the smallest of those
   big values on top, which is exactly the k-th largest.

2) Quickselect (Lomuto partition):
   This is the expected-linear-time selection algorithm based on quicksort's
   partition step. Pick a pivot (here randomized), partition the array so that
   elements <= pivot are on the left and > pivot on the right, then recurse only
   into the side that contains the target index. We look for index
   len(nums) - k in ascending order, which corresponds to the k-th largest.
   Randomization guarantees O(n) expected time and avoids the O(n^2) worst case
   on already-sorted / adversarial inputs.

Complexity:
- Heap approach:
    Time: O(n log k)  -- n insertions/removals, each O(log k).
    Space: O(k) for the heap.
- Quickselect:
    Time: O(n) expected, O(n^2) worst case (rare with randomization).
    Space: O(1) extra (in-place; recursion depth O(log n) expected).
"""

import heapq
import random
from typing import List


class Solution:
    # ---------------- Solution 1: Min-heap of size k ----------------
    def findKthLargest_heap(self, nums: List[int], k: int) -> int:
        """Use a min-heap of size k to track the k largest elements."""
        min_heap: List[int] = []
        for num in nums:
            heapq.heappush(min_heap, num)
            if len(min_heap) > k:
                heapq.heappop(min_heap)  # discard the smallest among the k+1
        # The heap root is the smallest of the k largest -> the k-th largest.
        return min_heap[0]

    # ---------------- Solution 2: Quickselect (Lomuto) ----------------
    def findKthLargest(self, nums: List[int], k: int) -> int:
        """Quickselect with randomized Lomuto partition."""
        # The k-th largest is the (n - k)-th element in 0-indexed ascending order.
        target_index = len(nums) - k
        left, right = 0, len(nums) - 1

        while left <= right:
            pivot_index = self._partition(nums, left, right)
            if pivot_index == target_index:
                return nums[pivot_index]
            elif pivot_index < target_index:
                left = pivot_index + 1
            else:
                right = pivot_index - 1

        # Should never reach here if inputs are valid.
        return -1

    def _partition(self, nums: List[int], left: int, right: int) -> int:
        """Lomuto partition with a randomized pivot.

        Places the pivot in its correct sorted position and returns that index.
        Elements <= pivot end up on the left, elements > pivot on the right.
        """
        # Random pivot avoids worst-case behavior on sorted inputs.
        pivot_idx = random.randint(left, right)
        nums[pivot_idx], nums[right] = nums[right], nums[pivot_idx]
        pivot = nums[right]

        # i marks the boundary of the "<= pivot" region.
        i = left
        for j in range(left, right):
            if nums[j] <= pivot:
                nums[i], nums[j] = nums[j], nums[i]
                i += 1
        # Put the pivot in its final position.
        nums[i], nums[right] = nums[right], nums[i]
        return i


if __name__ == "__main__":
    sol = Solution()
    print(sol.findKthLargest([3, 2, 1, 5, 6, 4], 2))  # 5
    print(sol.findKthLargest_heap([3, 2, 1, 5, 6, 4], 2))  # 5
    print(sol.findKthLargest([3, 2, 3, 1, 2, 4, 5, 5, 6], 4))  # 4
