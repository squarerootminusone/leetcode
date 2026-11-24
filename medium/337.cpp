/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    // taken, not taken
    pair<int, int> robRec(TreeNode* node) {
        if (node->left == nullptr && node->right == nullptr)
            return {node->val, 0};

        if (node->left != nullptr && node->right !=nullptr) {
            pair<int, int> l = robRec(node->left);
            pair<int, int> r = robRec(node->right);
            return {l.second + r.second + node->val, max(l.first, l.second) + max(r.first, r.second)};
        }

        pair<int, int> c = robRec(node->left == nullptr ? node->right : node->left);
        return {c.second + node->val, max(c.first, c.second)};
    }

public:
    int rob(TreeNode* root) {
        pair<int, int> res = robRec(root);
        return max(res.first, res.second);
    }
};
