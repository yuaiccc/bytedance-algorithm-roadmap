/**
 * LeetCode 133 - Clone Graph
 * https://leetcode.com/problems/clone-graph/
 * Difficulty: Medium
 *
 * Problem:
 * Given a reference to a node in a connected undirected graph, return a deep
 * copy (clone) of the graph. Each node has an integer value and a list of
 * neighbors.
 *
 * Approach:
 * DFS with a hash map (original node -> cloned node). For each node:
 *   - If it was already cloned, return the cached clone (handles cycles).
 *   - Otherwise create a new clone, record it in the map, then recursively
 *     clone each neighbor and append to the clone's neighbor list.
 * The map both memoizes clones and prevents infinite loops on cycles.
 *
 * Complexity:
 * - Time: O(V + E) — each node and edge visited once.
 * - Space: O(V) — for the hash map and recursion stack.
 */

#include <bits/stdc++.h>
using namespace std;

// Definition for a graph node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() : val(0), neighbors() {}
    Node(int _val) : val(_val), neighbors() {}
    Node(int _val, vector<Node*> _neighbors) : val(_val), neighbors(_neighbors) {}
};

class Solution {
    unordered_map<Node*, Node*> cloned; // original -> clone

public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) return nullptr;

        // Return the cached clone if we've already created it (cycle guard).
        if (cloned.count(node)) return cloned[node];

        // Create the clone and cache it BEFORE recursing (cycle safety).
        Node* copy = new Node(node->val);
        cloned[node] = copy;

        // Recursively clone all neighbors.
        for (Node* neighbor : node->neighbors) {
            copy->neighbors.push_back(cloneGraph(neighbor));
        }
        return copy;
    }
};

// ---- Helper: build a graph from adjacency list and verify clone ----
Node* buildGraph(const vector<vector<int>>& adj) {
    if (adj.empty()) return nullptr;
    vector<Node*> nodes(adj.size() + 1);
    for (int i = 1; i <= (int)adj.size(); ++i)
        nodes[i] = new Node(i);
    for (int i = 1; i <= (int)adj.size(); ++i)
        for (int nb : adj[i - 1])
            nodes[i]->neighbors.push_back(nodes[nb]);
    return nodes[1];
}

int main() {
    Solution sol;
    // adjList = [[2,4],[1,3],[2,4],[1,3]]
    Node* graph = buildGraph({{2, 4}, {1, 3}, {2, 4}, {1, 3}});
    Node* clonedGraph = sol.cloneGraph(graph);
    cout << clonedGraph->val << endl; // 1
    cout << clonedGraph->neighbors.size() << endl; // 2
    return 0;
}
