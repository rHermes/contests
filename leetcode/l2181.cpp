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
  static constexpr ListNode* mergeNodes(ListNode* head)
  {
    auto curHead = head->next;
    auto root = curHead;
    while (true) {
      if (!curHead) {
        break;
      }

      auto nextSpot = curHead->next;
      while (nextSpot->val != 0) {
        curHead->val += nextSpot->val;
        nextSpot = nextSpot->next;
      }

      curHead->next = nextSpot->next;
      curHead = curHead->next;
    }

    return root;
  }
};
