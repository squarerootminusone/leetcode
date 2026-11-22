class Solution {
    // returns <needs parent, camera here, covered without parent>
    array<int, 3> rec(TreeNode* root) {
        if (!root->left && !root->right)
            return {0, 1, 1};

        if (root->left && root->right) {
            auto l = rec(root->left), r = rec(root->right);
            int cam = 1 + min(l[0], l[1]) + min(r[0], r[1]);
            return {l[2] + r[2], cam, min({cam, l[1] + r[2], l[2] + r[1]})};
        }

        auto c = rec(root->left ? root->left : root->right);
        int cam = 1 + min(c[0], c[1]);
        return {c[2], cam, min(cam, c[1])};
    }

public:
    int minCameraCover(TreeNode* root) {
        return rec(root)[2];
    }
};
