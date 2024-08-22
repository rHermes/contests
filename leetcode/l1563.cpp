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
  static int solve(const std::vector<int>& psa, std::vector<int>& cache, const int N, const int l, const int r)
  {

    if (l == r) {
      return 0;
    }

    const int key = l * N + r;
    if (cache[key] != -1) {
      return cache[key];
    }

    int ans = std::numeric_limits<int>::lowest();

    for (int i = l; i < r; i++) {
      const int leftSide = psa[i + 1] - psa[l];
      const int rightSide = psa[r + 1] - psa[i + 1];

      if (leftSide < rightSide) {
        ans = std::max(ans, leftSide + solve(psa, cache, N, l, i));
      } else if (rightSide < leftSide) {
        ans = std::max(ans, rightSide + solve(psa, cache, N, i + 1, r));
      } else {
        ans = std::max(ans, leftSide + solve(psa, cache, N, l, i));
        ans = std::max(ans, rightSide + solve(psa, cache, N, i + 1, r));
      }
    }

    cache[key] = ans;
    return ans;
  }

public:
  static int stoneGameV(const std::vector<int>& stoneValue)
  {
    const int N = stoneValue.size();

    std::vector<int> psa(N + 1);
    for (int i = 0; i < N; i++) {
      psa[i + 1] = psa[i] + stoneValue[i];
    }

    std::vector<int> cache(N * N, -1);
    return solve(psa, cache, N, 0, N - 1);
  }
};
