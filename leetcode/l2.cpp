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
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
  {
    int carry = 0;
    auto root = l1;

    auto prev = l1;
    while (l1 != nullptr && l2 != nullptr) {
      prev = l1;

      carry += l1->val + l2->val;
      l1->val = carry % 10;
      carry /= 10;

      l1 = l1->next;
      l2 = l2->next;
    }

    if (l1 == nullptr) {
      prev->next = l2;
    }

    auto cur = prev->next;
    while (cur != nullptr) {
      prev = cur;

      carry += cur->val;
      cur->val = carry % 10;
      carry /= 10;

      cur = cur->next;
    }

    while (carry != 0) {
      auto ptr = new ListNode(carry % 10);
      carry /= 10;

      prev->next = ptr;
    }

    return root;
  }
};
