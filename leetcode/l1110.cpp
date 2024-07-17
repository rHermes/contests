#include <iostream>
#include <unordered_set>
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

  static TreeNode* dfs(std::vector<TreeNode*>& out, const std::unordered_set<int>& reject, TreeNode* root)
  {
    if (!root) {
      return nullptr;
    }

    // This will either be the child, or a nullptr;
    root->left = dfs(out, reject, root->left);
    root->right = dfs(out, reject, root->right);

    if (reject.count(root->val)) {
      if (root->left)
        out.push_back(root->left);

      if (root->right)
        out.push_back(root->right);

      delete root;
      return nullptr;
    }

    return root;
  }

public:
  static std::vector<TreeNode*> delNodes(TreeNode* root, const std::vector<int>& to_delete)
  {
    const std::unordered_set<int> reject(to_delete.begin(), to_delete.end());

    std::vector<TreeNode*> ans;
    if (dfs(ans, reject, root))
      ans.push_back(root);

    return ans;
  }
};
