#include <iostream>
#include <limits>
#include <unordered_map>
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
  static int minSubarray(const std::vector<int>& nums, const int p)
  {
    constexpr auto pmod = [](int x, const int p) {
      x %= p;
      if (x < 0)
        x += p;
      return x;
    };

    const int N = nums.size();

    int allP = 0;
    for (int i = 0; i < N; i++) {
      allP = (nums[i] + allP) % p;
    }
    if (allP == 0)
      return 0;

    // This is the rightmost index, such that the key is the given prefix
    // sum.
    std::unordered_map<int, int> dp;
    dp[0] = -1;

    int ans = std::numeric_limits<int>::max();

    int leftSum = 0;
    for (int i = 0; i < N; i++) {
      leftSum = (leftSum + nums[i]) % p;

      const int target = pmod(leftSum - allP, p);

      if (auto it = dp.find(target); it != dp.end()) {
        ans = std::min(ans, i - it->second);
      }
      dp[leftSum] = i;
    }

    if (N <= ans) {
      return -1;
    } else {
      return ans;
    }
  }
};
