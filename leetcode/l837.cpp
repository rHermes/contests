#include <array>
#include <iostream>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  constexpr static double new21Game(int n, int k, int maxPts)
  {
    if (k == 0 || (k + maxPts <= n))
      return 1.0;
    std::array<double, 10001> dp;

    dp[0] = 1;

    double runningSum = 1;
    double ans = 0;
    for (int i = 1; i <= n; i++) {
      dp[i] = runningSum / maxPts;
      if (i < k)
        runningSum += dp[i];
      else
        ans += dp[i];

      if (maxPts <= i)
        runningSum -= dp[i - maxPts];
    }

    return ans;
  }
};
