#include <bitset>
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
  static constexpr ListNode* modifiedList(const std::vector<int>& nums, ListNode* head)
  {
    // this is stupid, but a bitset is large enough for the input.
    // The more reasonable solution is to use a unordered_set, or even to just sort the nums list and do a binary search
    // within it.
    std::bitset<100000> block;
    for (const auto x : nums) {
      block[x - 1] = true;
    }

    // Find the first good node.
    while (block[head->val - 1]) {
      head = head->next;
    }

    auto cur = head;
    while (cur->next) {
      if (block[cur->next->val - 1]) {
        cur->next = cur->next->next;
      } else {
        cur = cur->next;
      }
    }

    return head;
  }
};
