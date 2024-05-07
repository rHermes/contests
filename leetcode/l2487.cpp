#include <iostream>
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
inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static ListNode* removeNodes(ListNode* head)
  {
    if (!head)
      return nullptr;

    head->next = removeNodes(head->next);
    if (!head->next)
      return head;

    if (head->val < head->next->val) {
      // we are leaking a node here, but that is ok.
      // but we assume the caller will clean up.
      return head->next;
    } else {
      return head;
    }
  }
};

int
main()
{
  return 0;
}
