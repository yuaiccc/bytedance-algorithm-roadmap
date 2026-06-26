"""
LeetCode 42 - Trapping Rain Water
https://leetcode.com/problems/trapping-rain-water/

Difficulty: Hard

Problem:
Given `n` non-negative integers representing an elevation map where the width of
each bar is 1, compute how much water it can trap after raining.

Approach (Two Pointers - O(n) time, O(1) space):
The water trapped above a single bar at index i is determined by the minimum of
the tallest bar to its left and the tallest bar to its right, minus the height
of bar i itself:

    water[i] = max(0, min(left_max[i], right_max[i]) - height[i])

A naive solution precomputes left_max[] and right_max[] arrays in O(n) space.
The two-pointer approach achieves the same result in O(1) extra space:

We maintain two pointers `left` (starting at 0) and `right` (starting at n-1),
and two running maxima `left_max` and `right_max`.

Core logic:
- If height[left] < height[right], then the water at `left` is bounded by
  left_max (because there exists some bar on the right that is at least as tall
  as height[right] > height[left]). So we process the left side:
    left_max = max(left_max, height[left])
    water   += left_max - height[left]
    left    += 1
- Otherwise, process the right side symmetrically:
    right_max = max(right_max, height[right])
    water    += right_max - height[right]
    right    -= 1

The invariant guaranteeing correctness: whenever we process `left`, we know
`left_max` is the true max to the left of `left`, and there is guaranteed to be
a bar on the right at least as tall as the current `left_max` (or taller), so
`left_max` is the limiting height. Symmetric for the right side.

Complexity:
- Time: O(n) - each bar is visited once.
- Space: O(1) - only a few variables used.
"""

from typing import List


class Solution:
    def trap(self, height: List[int]) -> int:
        if not height:
            return 0

        left, right = 0, len(height) - 1
        left_max, right_max = 0, 0
        water = 0

        while left < right:
            # Process the side with the smaller height.
            # The smaller side determines the water level at that position.
            if height[left] < height[right]:
                if height[left] >= left_max:
                    # New highest bar on the left; no water trapped here.
                    left_max = height[left]
                else:
                    # Water trapped = left_max - current height.
                    water += left_max - height[left]
                left += 1
            else:
                if height[right] >= right_max:
                    # New highest bar on the right; no water trapped here.
                    right_max = height[right]
                else:
                    # Water trapped = right_max - current height.
                    water += right_max - height[right]
                right -= 1

        return water


# ---------------------------------------------------------------------------
# Alternative: prefix/suffix max arrays (O(n) time, O(n) space) for reference
# ---------------------------------------------------------------------------
class SolutionArray:
    def trap(self, height: List[int]) -> int:
        n = len(height)
        if n == 0:
            return 0

        left_max = [0] * n
        right_max = [0] * n
        left_max[0] = height[0]
        right_max[n - 1] = height[n - 1]

        for i in range(1, n):
            left_max[i] = max(left_max[i - 1], height[i])
        for i in range(n - 2, -1, -1):
            right_max[i] = max(right_max[i + 1], height[i])

        water = 0
        for i in range(n):
            water += min(left_max[i], right_max[i]) - height[i]
        return water


# ---------------------------------------------------------------------------
# Example usage / quick test
# ---------------------------------------------------------------------------
if __name__ == "__main__":
    sol = Solution()
    print(sol.trap([0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]))  # 6
    print(sol.trap([4, 2, 0, 3, 2, 5]))                     # 9
