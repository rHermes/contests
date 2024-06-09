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
  static int palindromePartition(const std::string& s, const int k)
  {
    const int N = s.size();
    const int ROW = k + 1;
    std::vector<int> dp((N + 1) * ROW, N);
    dp[0 + 0] = 0;

    std::vector<int> cache(N * N);

    for (int r = 0; r < N; r++) {
      for (int l = 0; l <= r; l++) {
        int hit = s[r] != s[l];
        if (1 < r - l)
          hit += cache[(r - 1) * N + l + 1];

        cache[r * N + l] = hit;

        for (int i = 1; i <= k; i++) {
          dp[(r + 1) * ROW + i] = std::min(dp[(r + 1) * ROW + i], hit + dp[l * ROW + i - 1]);
        }
      }
    }
    return dp[N * ROW + k];
  }
};
