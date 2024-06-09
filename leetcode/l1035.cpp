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
  [[gnu::pure]] static int maxUncrossedLines(const std::vector<int>& nums1, const std::vector<int>& nums2)
  {
    const int N = nums1.size();
    const int M = nums2.size();

    const int ROW = (M + 1);

    std::vector<int> dp(ROW, 0);
    std::vector<int> prevDP(ROW, 0);

    for (int i = N - 1; 0 <= i; i--) {
      for (int j = M - 1; 0 <= j; j--) {
        if (nums1[i] == nums2[j]) {
          dp[j] = 1 + prevDP[j + 1];
        } else {
          dp[j] = std::max(dp[j + 1], prevDP[j]);
        }
      }

      std::swap(prevDP, dp);
    }

    return prevDP[0];
  }
};
