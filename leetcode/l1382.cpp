#include <bit>
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
  static constexpr void rotateLeft(TreeNode* parent, TreeNode* child)
  {
    // The left of the child will be the new root
    parent->right = child->right;

    // The left of the new
    child->right = parent->right->left;
    parent->right->left = child;
  }

  static constexpr void rotateRight(TreeNode* parent, TreeNode* child)
  {
    // The left of the child will be the new root
    parent->right = child->left;

    child->left = parent->right->right;
    parent->right->right = child;
  }

  static constexpr void makeRotations(TreeNode* vineHead, int count)
  {
    auto current = vineHead;
    for (int i = 0; i < count; i++) {
      rotateLeft(current, current->right);
      current = current->right;
    }
  }

public:
  static TreeNode* balanceBST(TreeNode* root)
  {
    TreeNode vineHead{};
    vineHead.right = root;

    auto psudoRoot = &vineHead;
    unsigned int count = -1;

    // we are going to keep rotating left while this happens.
    while (psudoRoot->right) {
      if (psudoRoot->right->left)
        rotateRight(psudoRoot, psudoRoot->right);
      else {
        psudoRoot = psudoRoot->right;
        count++;
      }
    }

    auto m = std::bit_floor(count) - 1;

    makeRotations(&vineHead, count - m);

    while (1 < m) {
      m /= 2;
      makeRotations(&vineHead, m);
    }

    return vineHead.right;
  }
};
