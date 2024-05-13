#include <iostream>
#include <vector>

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
  static ListNode* reverseKGroup(ListNode* head, int k)
  {
    std::vector<ListNode*> st;

    ListNode* newHead = nullptr;
    ListNode* prevHead = nullptr;
    while (head != nullptr) {
      st.push_back(head);
      head = head->next;

      if (st.size() == static_cast<std::size_t>(k)) {
        if (!newHead) {
          newHead = st.back();
        }

        if (prevHead)
          prevHead->next = st.back();

        // ok now we need to reverse this.
        while (1 < st.size()) {
          auto src = st.back();
          st.pop_back();
          src->next = st.back();
        }

        // now we need to put this one to next.
        st.back()->next = head;

        prevHead = st.back();
        st.pop_back();
      }
    }

    return newHead ? newHead : head;
  }
};

int
main()
{
  return 0;
}
