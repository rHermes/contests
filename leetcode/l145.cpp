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
  static constexpr std::vector<int> postorderTraversal(const TreeNode* root)
  {
    if (!root) {
      return {};
    }

    std::vector<int> out;
    std::vector<std::pair<const TreeNode*, bool>> st;
    out.reserve(100);
    st.reserve(100);

    st.emplace_back(root, false);

    while (!st.empty()) {
      const auto [cur, terminal] = std::move(st.back());
      st.pop_back();

      if (terminal) {
        out.push_back(cur->val);
      } else {
        st.emplace_back(cur, true);

        if (cur->right)
          st.emplace_back(cur->right, false);

        if (cur->left)
          st.emplace_back(cur->left, false);
      }
    }

    return out;
  }
};
