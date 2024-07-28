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
  static constexpr TreeNode* constructMaximumBinaryTree(const std::vector<int>& nums)
  {
    std::vector<std::pair<TreeNode*, int>> st;
    st.reserve(nums.size());

    for (const auto x : nums) {
      auto cur = new TreeNode(x);

      while (!st.empty() && st.back().second < x) {
        cur->left = st.back().first;
        st.pop_back();
      }

      if (!st.empty())
        st.back().first->right = cur;

      st.emplace_back(cur, x);
    }

    return st.empty() ? nullptr : st.front().first;
  }
};
