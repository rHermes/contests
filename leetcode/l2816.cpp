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
private:
  static ListNode* reverse(ListNode* head)
  {
    ListNode* prev = nullptr;

    while (head) {
      auto next = head->next;
      head->next = prev;
      prev = head;
      head = next;
    }

    return prev;
  }

public:
  static ListNode* doubleIt(ListNode* head)
  {
    head = reverse(head);

    ListNode* prev = nullptr;

    int carry = 0;
    while (head) {
      auto next = head->next;
      int sum = carry + 2 * head->val;

      head->val = sum % 10;
      carry = sum / 10;

      head->next = prev;
      prev = head;
      head = next;
    }

    head = prev;
    while (carry) {
      head = new ListNode(carry % 10, head);
      carry /= 10;
    }

    return head;
  }
};

int
main()
{
  return 0;
}
