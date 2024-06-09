#include <cstdint>
#include <iostream>
#include <unordered_map>
inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  std::unordered_map<std::int64_t, int> dp;

  int best(const std::int64_t x, const std::int64_t target)
  {
    if (target < x) {
      return std::min(1 + 2 * (target - 1), 2 * (x - target));
    }

    if (auto it = dp.find(target); it != dp.end()) {
      return it->second;
    }

    int moves = 0;
    std::int64_t cur = x;
    while (cur * x <= target) {
      cur *= x;
      moves++;
    }

    if (cur == target) {
      dp[target] = moves;
      return moves;
    }

    int ans = moves + 1 + best(x, target - cur);
    if (cur * x - target < target - cur)
      ans = std::min(ans, moves + 2 + best(x, cur * x - target));

    dp[target] = ans;
    return ans;
  }

public:
  int leastOpsExpressTarget(int x, int target)
  {
    if (target == 0)
      return 1;

    if (target == x)
      return 0;

    return best(x, target);
  }
};
