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
  static int maxProfit(const std::vector<int>& prices)
  {
    if (prices.empty())
      return 0;

    // The idea is as follows.
    // we make some profit p1, by buying in the current climate.
    //
    // Now we are excited to buy another stock to earn more profit.
    // Now the price for the second stock is going to be x-p1, as
    // we earned some on the first trade.
    //
    // Then if we sell the second stock at price y, your not profit p2
    // will be p2 = y - (x - p1);
    //
    // We don't have to do anything here, but focus on maximizing p2.

    int buy1 = std::numeric_limits<int>::max();
    int profit1 = 0;
    int buy2 = std::numeric_limits<int>::max();
    int profit2 = 0;

    for (const auto price : prices) {
      buy1 = std::min(buy1, price);
      profit1 = std::max(profit1, price - buy1);

      buy2 = std::min(buy2, price - profit1);
      profit2 = std::max(profit2, price - buy2);
    }

    return profit2;
  }
};
