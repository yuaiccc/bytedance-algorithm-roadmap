/**
 * LeetCode 1530 - Number of Good Leaf Nodes Pairs
 * https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/
 * Difficulty: Medium
 *
 * Problem:
 * Given the root of a binary tree and an integer distance, a pair of two
 * different leaf nodes is "good" if the length of the shortest path between
 * them is <= distance. Return the number of good leaf node pairs.
 *
 * Approach:
 * Post-order DFS. For each node, compute a list of distances from that node to
 * every leaf in its subtree. At an internal node, for each pair (a in left
 * subtree, b in right subtree) the path length between the two leaves is
 * a + b (since they meet at this node). Count pairs where a + b <= distance.
 * Then bubble up distances increased by 1 (one extra edge to the parent),
 * pruning any distance that already exceeds `distance` (it can never form a
 * valid pair higher up). A leaf node returns {0} (distance 0 to itself).
 *
 * Complexity:
 * - Time: O(n * d^2) in the worst case where d = distance; with d <= 10 this
 *   is effectively O(n).
 * - Space: O(n) for recursion + per-node distance lists.
 */

#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    int goodPairs = 0;
    int maxDist;

    // Returns list of distances from `node` to leaves in its subtree.
    vector<int> dfs(TreeNode* node) {
        if (node == nullptr) return {};

        // Leaf node: distance to itself is 0.
        if (node->left == nullptr && node->right == nullptr) {
            return {0};
        }

        vector<int> leftDists = dfs(node->left);
        vector<int> rightDists = dfs(node->right);

        // Count good pairs whose path passes through this node.
        for (int a : leftDists) {
            for (int b : rightDists) {
                if (a + 1 + b + 1 <= maxDist) ++goodPairs;
            }
        }

        // Bubble up distances incremented by 1 (edge to parent).
        // Prune distances that already exceed maxDist (can't be useful higher).
        vector<int> result;
        for (int a : leftDists) {
            if (a + 1 < maxDist) result.push_back(a + 1);
        }
        for (int b : rightDists) {
            if (b + 1 < maxDist) result.push_back(b + 1);
        }
        return result;
    }

public:
    int countPairs(TreeNode* root, int distance) {
        goodPairs = 0;
        maxDist = distance;
        dfs(root);
        return goodPairs;
    }
};

// ---- Helper: build tree from level-order vector (-1 = null) ----
TreeNode* buildTree(const vector<int>& vals) {
    if (vals.empty() || vals[0] == -1) return nullptr;
    TreeNode* root = new TreeNode(vals[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    while (!q.empty() && i < (int)vals.size()) {
        TreeNode* node = q.front(); q.pop();
        if (i < (int)vals.size() && vals[i] != -1) {
            node->left = new TreeNode(vals[i]);
            q.push(node->left);
        }
        i++;
        if (i < (int)vals.size() && vals[i] != -1) {
            node->right = new TreeNode(vals[i]);
            q.push(node->right);
        }
        i++;
    }
    return root;
}

int main() {
    Solution sol;
    // root = [1,2,3,-1,4], distance = 3 => 1
    TreeNode* t1 = buildTree({1, 2, 3, -1, 4});
    cout << sol.countPairs(t1, 3) << endl; // 1

    // root = [1,2,3,4,5,6,7], distance = 3 => 2
    TreeNode* t2 = buildTree({1, 2, 3, 4, 5, 6, 7});
    cout << sol.countPairs(t2, 3) << endl; // 2
    return 0;
}
