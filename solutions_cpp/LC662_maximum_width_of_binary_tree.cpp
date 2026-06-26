/**
 * LeetCode 662 - Maximum Width of Binary Tree
 * https://leetcode.com/problems/maximum-width-of-binary-tree/
 * Difficulty: Medium
 *
 * Problem:
 * Given the root of a binary tree, return the maximum width among all levels.
 * The width of one level is the distance between the leftmost and rightmost
 * non-null nodes at that level (null nodes between them ARE counted).
 *
 * Approach:
 * Assign every node a heap-style index: root = 1, left child = 2*parent,
 * right child = 2*parent + 1. Perform a level-order BFS storing each node with
 * its index. For each level the width is (rightmost_index - leftmost_index + 1).
 * Using unsigned long long prevents overflow on deep trees. The maximum width
 * over all levels is the answer.
 *
 * Complexity:
 * - Time: O(n) — each node visited once.
 * - Space: O(n) — queue can hold up to one full level.
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
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (root == nullptr) return 0;

        // Queue stores (node, index) pairs.
        queue<pair<TreeNode*, unsigned long long>> q;
        q.push({root, 0});

        int maxWidth = 0;

        while (!q.empty()) {
            int levelSize = (int)q.size();
            unsigned long long left = q.front().second;  // leftmost index this level
            unsigned long long right = left;

            for (int i = 0; i < levelSize; ++i) {
                auto [node, idx] = q.front();
                q.pop();
                right = idx; // keep updating; last one is rightmost

                // Heap-style indexing.
                if (node->left)  q.push({node->left,  2 * idx});
                if (node->right) q.push({node->right, 2 * idx + 1});
            }

            int width = (int)(right - left + 1);
            maxWidth = max(maxWidth, width);
        }

        return maxWidth;
    }
};

// ---- Helper: build tree from level-order vector (use -1 for null) ----
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
    // root = [1,3,2,5,3,null,9] => width 4
    TreeNode* t1 = buildTree({1, 3, 2, 5, 3, -1, 9});
    cout << sol.widthOfBinaryTree(t1) << endl; // 4

    // root = [1,3,2,5,null,null,9,6,null,null,7] => width 8
    // (LeetCode serialization omits children of null nodes.)
    TreeNode* t2 = buildTree({1, 3, 2, 5, -1, -1, 9, 6, -1, -1, 7});
    cout << sol.widthOfBinaryTree(t2) << endl; // 8
    return 0;
}
