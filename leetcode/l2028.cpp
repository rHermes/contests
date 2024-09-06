#include <algorithm>
#include <iostream>
#include <numeric>
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
  static std::vector<int> missingRolls(const std::vector<int>& rolls, const int mean, const int N)
  {
    const int M = rolls.size();
    const int TN = M + N;
    const int TOTAL = TN * mean;

    const int rollSum = std::reduce(rolls.begin(), rolls.end(), 0);
    if (TOTAL < (rollSum + N) || (rollSum + 6 * N) < TOTAL) {
      return {};
    }

    std::vector<int> out(N, 1);
    int curLeft = TOTAL - rollSum - N;
    auto itBP = std::ranges::fill_n(out.begin(), curLeft / 5, 6);
    curLeft %= 5;
    if (0 < curLeft) {
      *itBP = curLeft + 1;
    }

    return out;
  }
};
