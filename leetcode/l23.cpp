/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include <cstddef>
#include <vector>

struct ListNode
{
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution
{
  ListNode* merge2Lists(ListNode* a, ListNode* b)
  {
    ListNode root;
    ListNode* prev = &root;

    while (a && b) {
      if (a->val < b->val) {
	prev->next = a;
	prev       = a;
	a          = a->next;
      } else {
	prev->next = b;
	prev       = b;
	b          = b->next;
      }
    }

    if (a) {
      prev->next = a;
    } else {
      prev->next = b;
    }

    return root.next;
  }

  ListNode* mergeSort(const std::vector<ListNode*>& lists, const std::size_t l, const std::size_t r)
  {
    if (l == r) {
      return lists[l];
    } else if (l + 1 == r) {
      return merge2Lists(lists[l], lists[r]);
    } else {
      const auto c  = (l + r) / 2;
      auto leftOne  = mergeSort(lists, l, c);
      auto rightOne = mergeSort(lists, c + 1, r);

      return merge2Lists(leftOne, rightOne);
    }
  }

public:
  ListNode* mergeKLists(std::vector<ListNode*>& lists)
  {
    if (lists.empty())
      return nullptr;

    return mergeSort(lists, 0, lists.size() - 1);
  }
};

int
main()
{
  return 0;
}
