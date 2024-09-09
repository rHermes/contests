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
  static std::vector<std::vector<int>> spiralMatrix(const int M, const int N, ListNode const* head)
  {
    std::vector<std::vector<int>> out(M, std::vector<int>(N, -1));

    const auto writeVal = [&](const int y, const int x) {
      if (head) {
        out[y][x] = head->val;
        head = head->next;
      }
    };

    // ok, we will loop in numbers.
    for (int iter = 0; head; iter++) {
      const int W = N - 2 * iter;
      const int H = M - 2 * iter;

      for (int j = 0; j < W; j++) {
        writeVal(iter, iter + j);
      }

      for (int j = 1; j < H; j++) {
        writeVal(iter + j, iter + W - 1);
      }

      for (int j = W - 2; 0 <= j; j--) {
        writeVal(iter + H - 1, iter + j);
      }

      for (int j = H - 2; 0 < j; j--) {
        writeVal(iter + j, iter);
      }
    }

    return out;
  }
};
