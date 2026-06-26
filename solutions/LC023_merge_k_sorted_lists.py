"""
LeetCode 23 - Merge k Sorted Lists
https://leetcode.com/problems/merge-k-sorted-lists/

Difficulty: Hard

Problem:
You are given an array of k linked-lists, each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.

Approach:
Use a min-heap (Python's heapq). Push the head node of every non-empty list into the
heap, keyed by (node.val, list_index, node). We include a unique list_index (or an
incrementing counter) in the tuple because heapq compares tuples element-wise, and
ListNode objects are not orderable — the tie-breaker prevents a direct comparison of
nodes. Repeatedly pop the smallest node, append it to the result, and if that node has
a next, push the next node back into the heap. This yields a fully sorted merge.

Complexity:
- Time: O(N log k), where N is the total number of nodes across all k lists.
  Each of the N nodes is pushed and popped once; each heap operation is O(log k).
- Space: O(k) for the heap, plus O(1) extra for pointers (the output reuses nodes).
"""

from __future__ import annotations

import heapq
from typing import List, Optional


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val: int = 0, next: Optional["ListNode"] = None):
        self.val = val
        self.next = next


class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        min_heap: list[tuple[int, int, ListNode]] = []

        # Seed the heap with the head of each non-empty list.
        # The middle counter ensures ListNode is never compared directly.
        for idx, node in enumerate(lists):
            if node is not None:
                heapq.heappush(min_heap, (node.val, idx, node))

        # Dummy head simplifies building the result list.
        dummy = ListNode(0)
        tail = dummy

        while min_heap:
            val, idx, node = heapq.heappop(min_heap)
            # Append the smallest node to the merged list
            tail.next = node
            tail = tail.next

            # If there is a next node in the same source list, push it
            if node.next is not None:
                heapq.heappush(min_heap, (node.next.val, idx, node.next))

        return dummy.next


# ---------------------------------------------------------------------------
# Helpers for testing
# ---------------------------------------------------------------------------
def _build_linked_list(values: List[int]) -> Optional[ListNode]:
    dummy = ListNode(0)
    tail = dummy
    for v in values:
        tail.next = ListNode(v)
        tail = tail.next
    return dummy.next


def _linked_list_to_list(head: Optional[ListNode]) -> List[int]:
    result: List[int] = []
    while head is not None:
        result.append(head.val)
        head = head.next
    return result


# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------
if __name__ == "__main__":
    sol = Solution()

    # Basic merge
    l1 = _build_linked_list([1, 4, 5])
    l2 = _build_linked_list([1, 3, 4])
    l3 = _build_linked_list([2, 6])
    assert _linked_list_to_list(sol.mergeKLists([l1, l2, l3])) == [1, 1, 2, 3, 4, 4, 5, 6]

    # Empty input
    assert sol.mergeKLists([]) is None

    # List of empty lists
    assert sol.mergeKLists([None, None]) is None

    # Single list
    single = _build_linked_list([1, 2, 3])
    assert _linked_list_to_list(sol.mergeKLists([single])) == [1, 2, 3]

    # Single element lists
    a = _build_linked_list([5])
    b = _build_linked_list([1])
    c = _build_linked_list([3])
    assert _linked_list_to_list(sol.mergeKLists([a, b, c])) == [1, 3, 5]

    print("All tests passed.")
