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
  static std::pair<int, int> solve(TreeNode* root)
  {
    if (root->left && root->right) {
      auto [lUD, lU] = solve(root->left);
      auto [rUD, rU] = solve(root->right);

      int U = std::max({ lU, rU, 0 }) + root->val;

      int UD = std::max(lUD, rUD);
      UD = std::max(UD, root->val + std::max(0, lU) + std::max(rU, 0));

      return { UD, U };
    } else if (root->left) {
      auto [lUD, lU] = solve(root->left);
      lU = root->val + std::max(lU, 0);
      lUD = std::max(lUD, lU);

      return { lUD, lU };
    } else if (root->right) {
      auto [rUD, rU] = solve(root->right);
      rU = root->val + std::max(rU, 0);
      rUD = std::max(rUD, rU);

      return { rUD, rU };
    } else {
      return { root->val, root->val };
    }
  }

public:
  static int maxPathSum(TreeNode* root)
  {
    const auto hey = solve(root);
    return hey.first;
  }
};

int
main()
{
  return 0;
}
