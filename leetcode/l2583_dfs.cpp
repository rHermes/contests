#include <algorithm>
#include <iostream>
#include <vector>

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
public:
  static long long kthLargestLevelSum(TreeNode* root, const int k)
  {
    std::vector<long long> ans;
    ans.reserve(100);

    // Ptr, depth
    std::vector<std::pair<TreeNode*, int>> Q;

    Q.emplace_back(root, 0);

    while (!Q.empty()) {
      const auto [curPtr, curDepth] = Q.back();
      Q.pop_back();

      if (curDepth == static_cast<int>(ans.size()))
        ans.emplace_back(curPtr->val);
      else
        ans[curDepth] += curPtr->val;

      if (curPtr->left)
        Q.emplace_back(curPtr->left, curDepth + 1);

      if (curPtr->right)
        Q.emplace_back(curPtr->right, curDepth + 1);
    }

    if (static_cast<int>(ans.size()) < k)
      return -1;

    // Find the nth element.
    std::ranges::nth_element(ans, ans.begin() + k - 1, std::ranges::greater{});
    return ans[k - 1];
  }
};
