"""
LeetCode 206 - Reverse Linked List
https://leetcode.com/problems/reverse-linked-list/

Difficulty: Easy

Problem:
Given the head of a singly linked list, reverse the list, and return the
reversed list.

Example:
    Input:  1 -> 2 -> 3 -> 4 -> 5
    Output: 5 -> 4 -> 3 -> 2 -> 1

Approach:
We provide two solutions:

1) Iterative (three pointers): Maintain three pointers prev, curr, nxt.
   At each step we redirect curr.next to prev, then advance all three forward.
   This reverses every link in a single pass.

2) Recursive: Recurse to the end of the list. On the way back, for each node
   we make node.next.next point back to node, then sever the forward link
   (node.next = None). The new head is the tail node returned from the
   deepest recursive call.

Complexity (both):
- Time: O(n) where n is the number of nodes (single traversal).
- Space:
    * Iterative: O(1) extra space.
    * Recursive: O(n) for the call stack.
"""

from typing import Optional


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        """Iterative solution using three pointers."""
        prev = None          # previous node (starts as None)
        curr = head          # current node we are processing

        while curr is not None:
            nxt = curr.next   # remember the next node before we overwrite it
            curr.next = prev  # reverse the link
            prev = curr       # move prev forward
            curr = nxt        # move curr forward

        # prev is now the new head (old tail); curr is None
        return prev

    def reverseListRecursive(self, head: Optional[ListNode]) -> Optional[ListNode]:
        """Recursive solution."""
        # Base case: empty list or single node -> already reversed
        if head is None or head.next is None:
            return head

        # Recursively reverse the rest of the list.
        # 'new_head' is the last node of the original list.
        new_head = self.reverseListRecursive(head.next)

        # head.next is the node right after head in the original order.
        # Point it back to head so the link is reversed.
        head.next.next = head
        head.next = None  # sever the old forward link

        return new_head


# --------------------- Helper utilities for testing ---------------------
def build_list(values):
    """Build a linked list from a Python list and return its head."""
    dummy = ListNode()
    tail = dummy
    for v in values:
        tail.next = ListNode(v)
        tail = tail.next
    return dummy.next


def to_list(head):
    """Convert a linked list back to a Python list."""
    result = []
    while head is not None:
        result.append(head.val)
        head = head.next
    return result


if __name__ == "__main__":
    sol = Solution()
    head = build_list([1, 2, 3, 4, 5])
    print(to_list(sol.reverseList(head)))                # [5, 4, 3, 2, 1]
    head = build_list([1, 2, 3, 4, 5])
    print(to_list(sol.reverseListRecursive(head)))       # [5, 4, 3, 2, 1]
