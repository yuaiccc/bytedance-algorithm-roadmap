"""
LeetCode 5 - Longest Palindromic Substring
https://leetcode.com/problems/longest-palindromic-substring/

Difficulty: Medium

Problem:
Given a string s, return the longest palindromic substring in s.

Approach:
Use the center expansion technique. Every palindrome has a center; for a string of
length n there are 2n - 1 possible centers (n single-character centers and n - 1
between-character centers). For each center, expand outward as long as the characters
on both sides match. Track the start index and length of the longest palindrome found.
This avoids extra memory for DP tables.

Complexity:
- Time: O(n^2) — for each of the O(n) centers we may expand up to O(n) steps
- Space: O(1) — only a few index variables are used (not counting the output string)
"""

from __future__ import annotations


class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        if n < 2:
            return s

        start = 0  # start index of the longest palindrome found so far
        max_len = 1  # length of the longest palindrome found so far

        def expand_around_center(left: int, right: int) -> tuple[int, int]:
            """Expand from center (left, right) and return (start, length)."""
            while left >= 0 and right < n and s[left] == s[right]:
                left -= 1
                right += 1
            # When the loop exits, s[left] != s[right] or bounds exceeded.
            # The valid palindrome is s[left + 1 .. right - 1].
            length = right - left - 1
            return left + 1, length

        for i in range(n):
            # Odd-length palindromes: single character center
            odd_start, odd_len = expand_around_center(i, i)
            if odd_len > max_len:
                start, max_len = odd_start, odd_len

            # Even-length palindromes: center between i and i + 1
            even_start, even_len = expand_around_center(i, i + 1)
            if even_len > max_len:
                start, max_len = even_start, even_len

        return s[start : start + max_len]


# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------
if __name__ == "__main__":
    sol = Solution()

    # Basic cases
    assert sol.longestPalindrome("babad") in ("bab", "aba"), "Expected 'bab' or 'aba'"
    assert sol.longestPalindrome("cbbd") == "bb", "Expected 'bb' for 'cbbd'"

    # Edge cases
    assert sol.longestPalindrome("a") == "a", "Expected 'a' for single char"
    assert sol.longestPalindrome("ac") in ("a", "c"), "Expected 'a' or 'c' for 'ac'"

    # Whole string is a palindrome
    assert sol.longestPalindrome("racecar") == "racecar", "Expected 'racecar'"
    assert sol.longestPalindrome("abba") == "abba", "Expected 'abba'"

    # Even-length palindrome in the middle
    assert sol.longestPalindrome("aacabdkacaa") == "aca", "Expected 'aca'"

    # No longer than 1 char palindrome
    assert sol.longestPalindrome("abcd") in ("a", "b", "c", "d"), "Expected single char"

    print("All tests passed.")
