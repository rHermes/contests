#include <algorithm>
#include <iostream>
#include <utility>

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
  static std::pair<int, int> minMax(const TreeNode* root, int& ans)
  {
    int mi = root->val;
    int ma = root->val;

    if (root->left) {
      const auto [lmi, lma] = minMax(root->left, ans);
      mi = std::min(lmi, mi);
      ma = std::max(lma, ma);
    }

    if (root->right) {
      const auto [rmi, rma] = minMax(root->right, ans);
      mi = std::min(rmi, mi);
      ma = std::max(rma, ma);
    }

    int maxAns = std::max(root->val - mi, ma - root->val);
    ans = std::max(ans, maxAns);
    return { mi, ma };
  }

public:
  static int maxAncestorDiff(const TreeNode* root)
  {
    int ans = 0;
    minMax(root, ans);
    return ans;
  }
};

int
main()
{
  return 0;
}
