#include <algorithm>
#include <iostream>
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
  static constexpr int stoneGameVI(const std::vector<int>& aliceValues, const std::vector<int>& bobValues)
  {
    const int N = aliceValues.size();

    int total = 0;
    std::vector<int> comb = aliceValues;
    for (int i = 0; i < N; i++) {
      total += comb[i];
      comb[i] += bobValues[i];
    }
    std::ranges::sort(comb, std::ranges::greater{});
    for (int i = 1; i < N; i += 2) {
      total -= comb[i];
    }

    if (total < 0) {
      return -1;
    } else if (0 < total) {
      return 1;
    } else {
      return 0;
    }
  }
};
