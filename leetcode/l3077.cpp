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
  static long long maximumStrength(const std::vector<int>& nums, int K)
  {
    const int N = nums.size();
    constexpr auto gidx = [](int col, bool set) { return col * 2 + set; };

    const long long sentinel = -std::numeric_limits<long long>::max();
    std::vector<long long> DP((K + 1) * 2, sentinel);

    DP[gidx(0, false)] = 0;
    auto NDP = DP;
    for (int i = N - 1; 0 <= i; i--) {
      for (int k = 1; k <= K; k++) {
        const long long getk = (k % 2 != 0) ? k : -k;
        const long long lel = nums[i];

        const auto nextGood = std::max(DP[gidx(k - 1, false)], DP[gidx(k, true)]);

        if (nextGood != sentinel)
          NDP[gidx(k, true)] = lel * getk + nextGood;

        NDP[gidx(k, false)] = std::max(DP[gidx(k, false)], NDP[gidx(k, true)]);
      }

      DP = NDP;
    }

    return DP[gidx(K, false)];
  }
};
