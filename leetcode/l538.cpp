
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
  constexpr int solve(TreeNode* root, int cur)
  {
    if (!root)
      return cur;

    int newCur = solve(root->right, cur);
    root->val += newCur;

    newCur = solve(root->left, root->val);
    return newCur;
  }

public:
  constexpr TreeNode* convertBST(TreeNode* root)
  {
    solve(root, 0);
    return root;
  }
};
