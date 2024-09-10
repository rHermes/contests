#include <iostream>
#include <numeric>

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
  static ListNode* insertGreatestCommonDivisors(ListNode* head)
  {
    auto out = head;

    while (head->next) {
      auto nextHead = head->next;

      const auto val = std::gcd(head->val, nextHead->val);
      head->next = new ListNode(val, nextHead);

      head = nextHead;
    }

    return out;
  }
};
