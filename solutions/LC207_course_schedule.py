"""
LeetCode 207 - Course Schedule
https://leetcode.com/problems/course-schedule/

Difficulty: Medium

Problem:
There are a total of numCourses courses you have to take, labeled from 0 to
numCourses - 1. You are given an array prerequisites where
prerequisites[i] = [a, b] indicates that you must take course b before
course a (i.e. b -> a). Return true if you can finish all courses.
Otherwise, return false. (Detect a cycle in the directed graph.)

Approach:
Model courses as nodes of a directed graph and prerequisites as directed edges
(b -> a). The problem reduces to detecting a cycle: if the graph has a cycle,
no valid course ordering exists. We use Kahn's algorithm (BFS topological sort):

1. Compute the indegree of every node.
2. Initialize a queue with all nodes whose indegree is 0 (no prerequisites).
3. Repeatedly remove a node from the queue (it can be taken now), and decrement
   the indegree of each of its neighbors. Whenever a neighbor's indegree drops
   to 0, enqueue it.
4. Count how many nodes were processed. If it equals numCourses, the graph is
   acyclic (return True); otherwise there is a cycle (return False).

Complexity:
- Time: O(V + E) where V = numCourses and E = number of prerequisite pairs.
  Building the graph, computing indegrees, and the BFS each touch every edge
  and vertex once.
- Space: O(V + E) for the adjacency list and indegree array and queue.
"""

from typing import List
from collections import deque


class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        """Return True iff all courses can be finished (graph is acyclic)."""
        # Build adjacency list and indegree array.
        # Edge direction: prerequisite b -> course a (must take b first)
        graph = [[] for _ in range(numCourses)]
        indegree = [0] * numCourses

        for course, prereq in prerequisites:
            graph[prereq].append(course)
            indegree[course] += 1

        # Seed the queue with all courses that have no prerequisites.
        queue = deque([i for i in range(numCourses) if indegree[i] == 0])

        taken = 0  # number of courses we can schedule
        while queue:
            node = queue.popleft()
            taken += 1
            for neighbor in graph[node]:
                indegree[neighbor] -= 1
                if indegree[neighbor] == 0:
                    queue.append(neighbor)

        # If we could schedule every course, there is no cycle.
        return taken == numCourses


# --------------------- Alternative: DFS cycle detection ---------------------
class SolutionDFS:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        """Detect a cycle via DFS with three-color marking (0/1/2)."""
        graph = [[] for _ in range(numCourses)]
        for course, prereq in prerequisites:
            graph[prereq].append(course)

        # state: 0 = unvisited, 1 = visiting (on current DFS path), 2 = visited
        state = [0] * numCourses

        def has_cycle(node: int) -> bool:
            if state[node] == 1:   # back edge -> cycle
                return True
            if state[node] == 2:   # already fully processed
                return False

            state[node] = 1  # mark as visiting
            for neighbor in graph[node]:
                if has_cycle(neighbor):
                    return True
            state[node] = 2  # mark as fully visited
            return False

        for i in range(numCourses):
            if has_cycle(i):
                return False
        return True


if __name__ == "__main__":
    sol = Solution()
    print(sol.canFinish(2, [[1, 0]]))        # True
    print(sol.canFinish(2, [[1, 0], [0, 1]]))  # False (cycle)
