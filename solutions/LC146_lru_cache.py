"""
LeetCode 146 - LRU Cache
https://leetcode.com/problems/lru-cache/

Difficulty: Medium

Problem:
Design a data structure that follows the constraints of a Least Recently Used
(LRU) cache. Implement the LRUCache class:
  - LRUCache(int capacity): initialize the cache with positive size `capacity`.
  - int get(int key): return the value of the `key` if it exists, otherwise -1.
  - void put(int key, int value): update the value of the `key` if present.
    Otherwise, add the key-value pair to the cache. If inserting causes the
    number of keys to exceed capacity, evict the least recently used key.

Both `get` and `put` must run in O(1) average time complexity.

Approach:
An LRU cache needs two things:
  1. O(1) key -> value lookup        -> a hash map (dictionary).
  2. O(1) "move to front" and "remove tail" -> a doubly linked list (DLL),
     where the head is most-recently-used and the tail is least-recently-used.

We provide TWO implementations:

  (A) OrderedDict version (simple, Pythonic):
      Python's collections.OrderedDict maintains insertion order and supports
      O(1) move-to-end and popitem(last=False). Using it keeps the code short
      and is perfectly acceptable in many contexts.

  (B) Doubly linked list + hash map version (interview-standard):
      We build a custom DLL with dummy `head` and `tail` sentinels to eliminate
      edge-case branching. The hash map maps key -> DLL node. On every access
      we move the node to the front (right after head). On eviction we remove
      the node right before tail.

Complexity (both versions):
- Time: get/put are O(1) average.
- Space: O(capacity) for the hash map and list nodes.
"""

from collections import OrderedDict


# ===========================================================================
# (A) Simple version using OrderedDict
# ===========================================================================
class LRUCacheOrderedDict:
    """LRU cache backed by collections.OrderedDict.

    OrderedDict.move_to_end(key) marks `key` as most recently used.
    OrderedDict.popitem(last=False) removes the first (oldest) item.
    """

    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache: OrderedDict[int, int] = OrderedDict()

    def get(self, key: int) -> int:
        if key not in self.cache:
            return -1
        # Mark as most recently used.
        self.cache.move_to_end(key)
        return self.cache[key]

    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            # Update value and move to front.
            self.cache.move_to_end(key)
            self.cache[key] = value
            return
        if len(self.cache) >= self.capacity:
            # Evict the least recently used (first inserted) item.
            self.cache.popitem(last=False)
        self.cache[key] = value


# ===========================================================================
# (B) Interview-standard version: manual doubly linked list + hash map
# ===========================================================================
class _DListNode:
    """Doubly linked list node."""

    __slots__ = ("key", "value", "prev", "next")

    def __init__(self, key: int = 0, value: int = 0):
        self.key = key
        self.value = value
        self.prev: "_DListNode | None" = None
        self.next: "_DListNode | None" = None


class LRUCache:
    """LRU cache using a hash map + custom doubly linked list.

    List layout (with sentinel head/tail):
        head <-> [MRU node] <-> ... <-> [LRU node] <-> tail
    Most-recently-used nodes sit right after `head`; least-recently-used
    sit right before `tail`. Sentinels remove all None-check edge cases.
    """

    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache: dict[int, _DListNode] = {}  # key -> node

        # Sentinel head and tail; real nodes live strictly between them.
        self.head = _DListNode()
        self.tail = _DListNode()
        self.head.next = self.tail
        self.tail.prev = self.head

    # ---- DLL helper methods (all O(1)) ---------------------------------
    def _remove(self, node: _DListNode) -> None:
        """Unlink `node` from the list."""
        prev_node = node.prev
        next_node = node.next
        prev_node.next = next_node
        next_node.prev = prev_node

    def _add_to_front(self, node: _DListNode) -> None:
        """Insert `node` right after the sentinel head (mark as MRU)."""
        node.prev = self.head
        node.next = self.head.next
        self.head.next.prev = node
        self.head.next = node

    def _move_to_front(self, node: _DListNode) -> None:
        """Move an existing node to the front (most recently used)."""
        self._remove(node)
        self._add_to_front(node)

    def _pop_tail(self) -> _DListNode:
        """Remove and return the least recently used node (right before tail)."""
        lru = self.tail.prev
        self._remove(lru)
        return lru

    # ---- Public API ----------------------------------------------------
    def get(self, key: int) -> int:
        if key not in self.cache:
            return -1
        node = self.cache[key]
        # Accessing a node makes it most recently used.
        self._move_to_front(node)
        return node.value

    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            # Update existing node and move to front.
            node = self.cache[key]
            node.value = value
            self._move_to_front(node)
            return

        # Create a new node.
        new_node = _DListNode(key, value)
        self.cache[key] = new_node
        self._add_to_front(new_node)

        # Evict the least recently used entry if over capacity.
        if len(self.cache) > self.capacity:
            lru = self._pop_tail()
            del self.cache[lru.key]


# ---------------------------------------------------------------------------
# Example usage / quick test
# ---------------------------------------------------------------------------
if __name__ == "__main__":
    # LeetCode example trace.
    lru = LRUCache(2)
    lru.put(1, 1)          # cache = {1=1}
    lru.put(2, 2)          # cache = {1=1, 2=2}
    print(lru.get(1))      # returns 1; cache = {2=2, 1=1}  (1 is now MRU)
    lru.put(3, 3)          # evicts key 2; cache = {1=1, 3=3}
    print(lru.get(2))      # returns -1 (not found)
    lru.put(4, 4)          # evicts key 1; cache = {3=3, 4=4}
    print(lru.get(1))      # returns -1 (not found)
    print(lru.get(3))      # returns 3
    print(lru.get(4))      # returns 4

    # Quick sanity check for the OrderedDict version.
    lru2 = LRUCacheOrderedDict(2)
    lru2.put(1, 1)
    lru2.put(2, 2)
    print(lru2.get(1))     # 1
    lru2.put(3, 3)         # evicts 2
    print(lru2.get(2))     # -1
