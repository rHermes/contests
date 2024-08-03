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
  static constexpr int maxDotProduct(const std::vector<int>& nums1, const std::vector<int>& nums2)
  {
    const int N = nums1.size();
    const int M = nums2.size();
    std::vector<int> dp(N * M, std::numeric_limits<int>::lowest());

    dp[0 * M + 0] = nums1[0] * nums2[0];

    for (int i = 1; i < M; i++) {
      dp[0 * M + i] = std::max(dp[0 * M + i - 1], nums1[0] * nums2[i]);
    }

    for (int i = 1; i < N; i++) {
      dp[i * M + 0] = std::max(dp[(i - 1) * M + 0], nums1[i] * nums2[0]);
    }

    for (int j = 1; j < N; j++) {
      for (int i = 1; i < M; i++) {
        const auto a = dp[(j - 1) * M + i];
        const auto c = dp[(j - 1) * M + i - 1];
        const auto b = dp[j * M + i - 1];
        const auto d = nums1[j] * nums2[i] + std::max(c, 0);

        dp[j * M + i] = std::max({ a, b, c, d });
      }
    }

    return dp.back();
  }
};
