#include <iostream>
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

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  static constexpr TreeNode* solve(TreeNode* root, int val, int depth, bool isLeft)
  {

    if (depth == 1) {
      if (isLeft)
        return new TreeNode(val, root, nullptr);
      else
        return new TreeNode(val, nullptr, root);
    }

    if (!root) {
      return nullptr;
    }

    root->left = solve(root->left, val, depth - 1, true);
    root->right = solve(root->right, val, depth - 1, false);
    return root;
  }

public:
  static constexpr TreeNode* addOneRow(TreeNode* root, int val, int depth) { return solve(root, val, depth, true); }
};
