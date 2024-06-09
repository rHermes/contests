#include <cstdint>
#include <iostream>
#include <string>
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
  static int numDistinct(const std::string& s, const std::string& t)
  {
    const int M = t.size();

    std::vector<std::uint32_t> dp(M + 1, 0);
    dp[0] = 1;

    for (const auto sc : s) {
      // We have to iterate backwards, to avoid double counting.
      for (int i = M - 1; 0 <= i; i--) {
        if (sc == t[i]) {
          dp[i + 1] += dp[i];
        }
      }
    }

    return dp[M];
  }
};
