#include <algorithm>
#include <limits>
#include <vector>

class Solution
{
public:
  static int coinChange(std::vector<int>& coins, int amount)
  {
    if (amount == 0)
      return 0;

    std::ranges::sort(coins);

    const auto sentinel = std::numeric_limits<int>::max();
    std::vector<int> dp(amount + 1, sentinel);
    dp[0] = 0;

    for (const auto c : coins) {
      for (int i = c; i <= amount; ++i) {
        if (dp[i - c] != sentinel) {
          dp[i] = std::min(dp[i], dp[i - c] + 1);
        }
      }
    }

    if (dp[amount] == sentinel)
      return -1;
    else
      return dp[amount];
  }
};
