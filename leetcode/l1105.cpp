#include <iostream>
#include <limits>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static int minHeightShelves(const std::vector<std::vector<int>>& books, int shelfWidth)
  {
    const int N = books.size();

    // This is the answer for books[i:]...
    std::vector<int> dp(N + 1);
    for (int i = N - 1; 0 <= i; i--) {
      int curWidth = 0;
      int maxHeight = 0;
      int bestAns = std::numeric_limits<int>::max();

      for (int k = i; k < N; k++) {
        curWidth += books[k][0];
        if (shelfWidth < curWidth)
          break;

        maxHeight = std::max(maxHeight, books[k][1]);
        bestAns = std::min(bestAns, maxHeight + dp[k + 1]);
      }

      dp[i] = bestAns;
    }

    return dp[0];
  }
};
