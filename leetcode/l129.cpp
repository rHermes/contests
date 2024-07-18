/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution
{
  static constexpr void dfs(int& ans, int cur, TreeNode* root)
  {
    cur = cur * 10 + root->val;
    if (!root->left && !root->right) {
      ans += cur;
      return;
    }

    if (root->left) {
      dfs(ans, cur, root->left);
    }

    if (root->right) {
      dfs(ans, cur, root->right);
    }
  }

public:
  static constexpr int sumNumbers(TreeNode* root)
  {
    int ans = 0;
    dfs(ans, 0, root);
    return ans;
  }
};
