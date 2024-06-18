#include <iostream>
#include <vector>

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
  static std::vector<ListNode*> splitListToParts(ListNode* head, int k)
  {
    std::vector<ListNode*> all;
    while (head) {
      all.emplace_back(head);
      head = head->next;
    }

    const int len = all.size();
    int chunk = len / k;

    std::vector<ListNode*> out;
    int idx = 0;
    int rest = len % k;

    while (idx < len) {
      int consume = chunk;
      if (0 < rest) {
        consume++;
        rest--;
      }

      out.push_back(all[idx]);
      all[idx + consume - 1]->next = nullptr;

      idx += consume;
    }
    out.resize(k, nullptr);
    return out;
  }
};
