/**
 * Definition for singly-linked list.
 */
#include <iostream>
#include <utility>

struct ListNode
{
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
  static void deleteNode(ListNode* node)
  {
    node->val = node->next->val;
    node->next = std::exchange(node->next->next, nullptr);
  }
};

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();
