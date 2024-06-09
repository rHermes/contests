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
  static constexpr long long getDescentPeriods(const std::vector<int>& prices)
  {
    long long ans = 0;

    const int N = prices.size();

    int l = 0;
    while (l < N) {
      int r = l + 1;
      while (r < N && (prices[r - 1] - 1) == prices[r])
        r++;

      long long len = r - l;
      long long combs = (len * (len + 1)) / 2;
      ans += combs;
      l = r;
    }
    return ans;
  }
};
