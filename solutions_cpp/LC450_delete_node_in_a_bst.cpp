/**
 * LeetCode 450 - Delete Node in a BST
 * https://leetcode.com/problems/delete-node-in-a-bst/
 * Difficulty: Medium
 *
 * Problem:
 * Given the root of a binary search tree and a key, delete the node with the
 * given key and return the (possibly new) root while maintaining the BST
 * property. The tree should remain a valid BST.
 *
 * Approach:
 * Recursively navigate to the target node:
 *   - If key < node->val, recurse left; if key > node->val, recurse right.
 *   - Once found, handle three cases:
 *       1) Leaf node (no children): simply return nullptr.
 *       2) One child: return that child (it replaces the deleted node).
 *       3) Two children: find the in-order successor (leftmost node of the
 *          right subtree), copy its value into the current node, then delete
 *          the successor from the right subtree.
 * Because the successor is the smallest value in the right subtree, replacing
 * with it preserves BST ordering.
 *
 * Complexity:
 * - Time: O(h) where h is the tree height (O(log n) balanced, O(n) skewed).
 * - Space: O(h) for the recursion stack.
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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return nullptr;

        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            // Found the node to delete.
            if (root->left == nullptr) return root->right; // case 1 & 2 (no left)
            if (root->right == nullptr) return root->left;  // case 2 (no right)

            // Case 3: two children. Find in-order successor (min of right subtree).
            TreeNode* succ = root->right;
            while (succ->left != nullptr) succ = succ->left;

            root->val = succ->val; // copy successor value up
            // Remove the successor from the right subtree.
            root->right = deleteNode(root->right, succ->val);
        }
        return root;
    }
};

// ---- Helper: build / print tree (level order) ----
TreeNode* insert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left = insert(root->left, val);
    else if (val > root->val) root->right = insert(root->right, val);
    return root;
}

void levelOrder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front(); q.pop();
        cout << node->val << " ";
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    cout << endl;
}

int main() {
    Solution sol;
    // Build BST: [5,3,6,2,4,-1,7], delete key=3
    TreeNode* root = nullptr;
    for (int v : {5, 3, 6, 2, 4, 7}) root = insert(root, v);
    root = sol.deleteNode(root, 3);
    levelOrder(root); // e.g. [5,4,6,2,-1,-1,7]
    return 0;
}
