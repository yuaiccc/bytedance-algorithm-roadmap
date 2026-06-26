"""
LeetCode 20 - Valid Parentheses
https://leetcode.com/problems/valid-parentheses/

Difficulty: Easy

Problem:
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
determine if the input string is valid. A string is valid if:
  1. Open brackets must be closed by the same type of brackets.
  2. Open brackets must be closed in the correct order.
  3. Every close bracket has a corresponding open bracket of the same type.

Approach:
Use a stack. Iterate over each character:
- If it is an opening bracket, push it onto the stack.
- If it is a closing bracket, check the top of the stack: it must be the matching
  opening bracket; otherwise the string is invalid. Pop the matching opener.
At the end, the stack must be empty (all openers were closed).

Complexity:
- Time: O(n), single pass through the string; each push/pop is O(1)
- Space: O(n) in the worst case (e.g., all opening brackets)
"""

from __future__ import annotations


class Solution:
    def isValid(self, s: str) -> bool:
        # Map each closing bracket to its matching opening bracket
        matching: dict[str, str] = {")": "(", "}": "{", "]": "["}
        stack: list[str] = []

        for ch in s:
            if ch in matching.values():
                # Opening bracket -> push onto the stack
                stack.append(ch)
            elif ch in matching:
                # Closing bracket -> must match the top of the stack
                if not stack or stack[-1] != matching[ch]:
                    return False
                stack.pop()
            else:
                # Per problem constraints this branch is unreachable,
                # but kept defensively for robustness.
                return False

        # Valid only if every opener was closed
        return not stack


# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------
if __name__ == "__main__":
    sol = Solution()

    # Valid cases
    assert sol.isValid("()") is True
    assert sol.isValid("()[]{}") is True
    assert sol.isValid("{[]}") is True
    assert sol.isValid("((()))") is True
    assert sol.isValid("") is True  # empty string is valid

    # Invalid cases
    assert sol.isValid("(]") is False
    assert sol.isValid("([)]") is False
    assert sol.isValid("(") is False  # unclosed opener
    assert sol.isValid("]") is False  # closer without opener
    assert sol.isValid("(()") is False
    assert sol.isValid("())") is False

    print("All tests passed.")
