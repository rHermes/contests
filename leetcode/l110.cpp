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
  static constexpr std::pair<bool, int> maxDepth(TreeNode* root)
  {
    if (!root)
      return { true, 0 };

    auto [lb, ld] = maxDepth(root->left);
    if (!lb)
      return { false, 0 };
    auto [rb, rd] = maxDepth(root->right);
    if (!rb)
      return { false, 0 };

    return { std::abs(ld - rd) < 2, 1 + std::max(ld, rd) };
  }

public:
  static constexpr bool isBalanced(TreeNode* root)
  {
    auto [good, dpt] = maxDepth(root);
    return good;
  }
};
