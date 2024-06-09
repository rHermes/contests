#include <algorithm>
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
  static std::pair<int, int> robIt(TreeNode* root)
  {
    if (!root)
      return { 0, 0 };

    const auto [linc, lexc] = robIt(root->left);
    const auto [rinc, rexc] = robIt(root->right);

    return { root->val + lexc + rexc, std::max(linc, lexc) + std::max(rinc, rexc) };
  }

public:
  static int rob(TreeNode* root)
  {
    const auto [inc, exc] = robIt(root);
    return std::max(inc, exc);
  }
};
