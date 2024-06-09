#include <iostream>
#include <queue>
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
  static int findMaximizedCapital(int k, int w, const std::vector<int>& profits, const std::vector<int>& capital)
  {
    const int N = profits.size();
    const auto sorterCapital = [](const auto& a, const auto& b) {
      if (a.second != b.second)
        return b.second < a.second;

      return a.first < b.first;
    };

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(sorterCapital)> discardPile;

    std::priority_queue<int> mainPile;

    for (int i = 0; i < N; i++) {
      if (w < capital[i]) {
        discardPile.emplace(profits[i], capital[i]);
      } else
        mainPile.emplace(profits[i]);
    }

    for (int i = 0; i < k; i++) {
      if (mainPile.empty())
        return w;

      // We are going to choose the top now.
      const auto topP = mainPile.top();
      mainPile.pop();
      w += topP;

      if (i == k)
        return w;

      while (!discardPile.empty()) {
        const auto [disP, disC] = discardPile.top();
        if (w < disC) {
          break;
        }

        mainPile.emplace(disP);
        discardPile.pop();
      }
    }

    return w;
  }
};
