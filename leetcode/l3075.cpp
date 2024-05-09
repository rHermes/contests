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
  constexpr static long long maximumHappinessSum(std::vector<int>& happiness, int k)
  {
    if constexpr (false) {
      // This is theoretically faster, but due to the way sort is implemented,
      // it will beat it out for these sizes.
      std::partial_sort(happiness.begin(), happiness.begin() + k, happiness.end(), std::greater<int>{});
    } else {
      std::ranges::sort(happiness, std::greater<int>());
    }
    long long ans = 0;
    for (int i = 0; i < k; i++) {
      ans += std::max(happiness[i] - i, 0);
    }

    return ans;
  }
};

int
main()
{
  return 0;
}
