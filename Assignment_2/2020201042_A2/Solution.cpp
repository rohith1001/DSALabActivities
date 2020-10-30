class Solution {
  public:
    TreeNode *upper_bound(TreeNode *root, int value) {
        ub = nullptr;
        do_upper_bound(root, value);
        return ub;
    }

    TreeNode *lower_bound(TreeNode *root, int value) {
        lb = nullptr;
        do_lower_bound(root, value);
        return lb;
    }

  private:
    void do_upper_bound(TreeNode *root, int value) {
        if (root == nullptr) {
            return;
        }
        if (root->value > value) {
            ub = root;
            do_upper_bound(root->left, value);
        } else {
            do_upper_bound(root->right, value);
        }
    }

    void do_lower_bound(TreeNode *root, int value) {
        if (root == nullptr) {
            return;
        }
        if (root->value >= value) {
            lb = root;
            do_lower_bound(root->left, value);
        } else {
            do_lower_bound(root->right, value);
        }
    }

  private:
    TreeNode *ub;
    TreeNode *lb;
};
