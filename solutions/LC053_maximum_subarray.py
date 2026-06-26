"""
LeetCode 53 - Maximum Subarray
https://leetcode.com/problems/maximum-subarray/

Difficulty: Medium

Problem:
Given an integer array `nums`, find the subarray (containing at least one number)
which has the largest sum, and return its sum.

Approach (Kadane's Algorithm - O(n) time, O(1) space):
We iterate through the array while maintaining two variables:
  - `current_sum`: the maximum sum of a subarray ending at the current position.
  - `max_sum`:     the global maximum subarray sum seen so far.

At each element `num`, we decide whether to:
  - Extend the previous subarray by adding `num` (current_sum + num), OR
  - Start a fresh subarray beginning at `num`.
We pick whichever is larger:
    current_sum = max(num, current_sum + num)
Then update the global answer:
    max_sum = max(max_sum, current_sum)

Intuition: if `current_sum` ever becomes negative, it can only drag down any
future subarray, so we "reset" by starting fresh at the current element.

Divide and Conquer (alternative, mentioned for interviews):
  - Split the array into two halves. The maximum subarray is either:
      (a) entirely in the left half,
      (b) entirely in the right half, or
      (c) crossing the midpoint (extends into both halves).
  - The crossing case is computed by scanning leftward from the midpoint for the
    best left sum, and rightward from midpoint+1 for the best right sum.
  - Recurse on the two halves and take the max of all three.
  - Time: O(n log n), Space: O(log n) recursion stack.
  Kadane's is strictly better in time, but divide-and-conquer is a good exercise
  and appears in some problem variants (e.g. "find the maximum subarray sum"
  where online/streaming constraints differ, or when asked to demonstrate
  mastery of the paradigm).

Complexity (Kadane's):
- Time: O(n) - single pass through the array.
- Space: O(1) - only two variables.
"""

from typing import List


class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        # Initialize with the first element (subarray must be non-empty).
        current_sum = nums[0]
        max_sum = nums[0]

        for num in nums[1:]:
            # Either extend the existing subarray or start a new one at `num`.
            current_sum = max(num, current_sum + num)
            # Update the global maximum.
            max_sum = max(max_sum, current_sum)

        return max_sum


# ---------------------------------------------------------------------------
# Optional: also return the actual subarray indices (follow-up variant)
# ---------------------------------------------------------------------------
class SolutionWithIndices:
    def maxSubArray(self, nums: List[int]) -> int:
        """Returns the max sum and the [start, end] indices of that subarray."""
        current_sum = nums[0]
        max_sum = nums[0]
        start = end = 0
        temp_start = 0

        for i in range(1, len(nums)):
            if nums[i] > current_sum + nums[i]:
                # Starting a new subarray here is better.
                current_sum = nums[i]
                temp_start = i
            else:
                current_sum += nums[i]

            if current_sum > max_sum:
                max_sum = current_sum
                start = temp_start
                end = i

        return max_sum  # indices: start..end


# ---------------------------------------------------------------------------
# Example usage / quick test
# ---------------------------------------------------------------------------
if __name__ == "__main__":
    sol = Solution()
    print(sol.maxSubArray([-2, 1, -3, 4, -1, 2, 1, -5, 4]))  # 6  -> [4,-1,2,1]
    print(sol.maxSubArray([1]))                               # 1
    print(sol.maxSubArray([5, 4, -1, 7, 8]))                 # 23
