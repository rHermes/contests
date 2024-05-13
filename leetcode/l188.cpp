#include <algorithm>
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
  static int maxProfit(const int k, const std::vector<int>& prices)
  {
    if (prices.empty())
      return 0;

    std::vector<int> buys(k, std::numeric_limits<int>::max());
    std::vector<int> profits(k, 0);

    for (const auto price : prices) {
      buys[0] = std::min(buys[0], price);
      profits[0] = std::max(profits[0], price - buys[0]);

      for (int i = 1; i < k; i++) {
        buys[i] = std::min(buys[i], price - profits[i - 1]);
        profits[i] = std::max(profits[i], price - buys[i]);
      }
    }

    return profits[k - 1];
  }
};

int
main()
{
  return 0;
}
