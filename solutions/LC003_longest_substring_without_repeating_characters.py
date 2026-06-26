"""
LeetCode 3 - Longest Substring Without Repeating Characters
https://leetcode.com/problems/longest-substring-without-repeating-characters/

Difficulty: Medium

Problem:
Given a string s, find the length of the longest substring without repeating characters.

Approach:
Use a sliding window with a hashmap. Maintain two pointers (left, right) defining
the current window. The hashmap stores the most recent index of each character seen.
As we expand the right pointer, if the character is already in the window (its recorded
index >= left), we jump the left pointer to one past that recorded index. This avoids
shrinking one step at a time and keeps the whole scan linear. We track the maximum
window length throughout.

Complexity:
- Time: O(n), each character is visited at most twice (once by right, once by left jump)
- Space: O(min(m, n)) where m is the charset/alphabet size; the hashmap holds at most
  the alphabet size or the string length, whichever is smaller.
"""

from __future__ import annotations


class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        # Map from character -> its most recent index in the string
        char_index: dict[str, int] = {}
        left = 0
        max_length = 0

        for right, ch in enumerate(s):
            # If this character was seen before AND that occurrence is inside
            # the current window, move left past it to keep the window unique.
            if ch in char_index and char_index[ch] >= left:
                left = char_index[ch] + 1

            # Update the character's latest index
            char_index[ch] = right

            # Window is [left, right], length = right - left + 1
            max_length = max(max_length, right - left + 1)

        return max_length


# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------
if __name__ == "__main__":
    sol = Solution()

    # Basic cases
    assert sol.lengthOfLongestSubstring("abcabcbb") == 3, "Expected 3 for 'abcabcbb'"
    assert sol.lengthOfLongestSubstring("bbbbb") == 1, "Expected 1 for 'bbbbb'"
    assert sol.lengthOfLongestSubstring("pwwkew") == 3, "Expected 3 for 'pwwkew'"

    # Edge cases
    assert sol.lengthOfLongestSubstring("") == 0, "Expected 0 for empty string"
    assert sol.lengthOfLongestSubstring(" ") == 1, "Expected 1 for single space"
    assert sol.lengthOfLongestSubstring("a") == 1, "Expected 1 for single char"
    assert sol.lengthOfLongestSubstring("au") == 2, "Expected 2 for 'au'"
    assert sol.lengthOfLongestSubstring("dvdf") == 3, "Expected 3 for 'dvdf'"

    # All unique characters
    assert sol.lengthOfLongestSubstring("abcdefg") == 7, "Expected 7 for 'abcdefg'"

    # Repeating pattern
    assert sol.lengthOfLongestSubstring("abba") == 2, "Expected 2 for 'abba'"

    print("All tests passed.")
