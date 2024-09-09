#include <iostream>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

/**
 * Definition for singly-linked list.
 */
struct ListNode
{
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};
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
class Solution
{
  static bool solve(const ListNode* head, const TreeNode* root, bool started)
  {
    if (head == nullptr) {
      return true;
    }

    if (root == nullptr) {
      return false;
    }

    bool ans = false;
    if (head->val == root->val) {
      ans = solve(head->next, root->left, true) || solve(head->next, root->right, true);
    }

    if (!ans && !started) {
      ans = solve(head, root->left, false) || solve(head, root->right, false);
    }

    return ans;
  }

public:
  static bool isSubPath(const ListNode* head, const TreeNode* root) { return solve(head, root, false); }
};
