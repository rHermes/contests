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

class BSTIterator
{
  std::vector<TreeNode*> path;

  void prep(TreeNode* root)
  {
    while (root) {
      path.push_back(root);
      root = root->left;
    }
  }

public:
  BSTIterator(TreeNode* root) { prep(root); }

  int next()
  {
    const auto cur = path.back();
    path.pop_back();

    prep(cur->right);
    return cur->val;
  }

  bool hasNext() { return !path.empty(); }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

int
main()
{
  return 0;
}
