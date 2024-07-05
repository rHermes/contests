#include <iostream>
#include <limits>
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
  static std::vector<int> nodesBetweenCriticalPoints(ListNode* head)
  {
    int minDist = std::numeric_limits<int>::max();
    int firstCrit = -1;
    int lastCrit = -1;

    auto curIdx = 1;
    auto ppValue = head->val;
    auto pValue = head->next->val;
    auto curNode = head->next->next;

    int prevCrit = -1;
    while (curNode) {
      auto cValue = curNode->val;

      auto isMaxima = ppValue < pValue && pValue > cValue;
      auto isMinima = ppValue > pValue && pValue < cValue;
      if (isMaxima || isMinima) {
        if (firstCrit == -1)
          firstCrit = curIdx;
        else
          lastCrit = curIdx;

        if (prevCrit != -1)
          minDist = std::min(minDist, curIdx - prevCrit);

        prevCrit = curIdx;
      }

      ppValue = pValue;
      pValue = curNode->val;
      curIdx++;
      curNode = curNode->next;
    }

    if (lastCrit == -1) {
      return { -1, -1 };
    }

    return { minDist, lastCrit - firstCrit };
  }
};
