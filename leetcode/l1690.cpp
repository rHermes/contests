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
  static constexpr int solve(const std::vector<int>& stones,
                             const int N,
                             std::vector<int>& cache,
                             const int l,
                             const int r)
  {
    const int key = l * N + r;
    if (cache[key] != -1) {
      return cache[key];
    }

    const int solve1 = solve(stones, N, cache, l + 2, r);
    const int solve2 = solve(stones, N, cache, l + 1, r - 1);
    const int solve3 = solve(stones, N, cache, l, r - 2);

    const int leftChoice = std::min(stones[l + 1] + solve1, stones[r] + solve2);
    const int rightChoice = std::min(stones[r - 1] + solve3, stones[l] + solve2);

    const int ans = std::max(leftChoice, rightChoice);
    cache[key] = ans;
    return ans;
  }

public:
  static constexpr int stoneGameVII(const std::vector<int>& stones)
  {
    const int N = stones.size();

    std::vector<int> cache(N * N, -1);
    for (int i = 0; i < N; i++) {
      cache[i * N + i] = 0;
    }
    for (int i = 0; i < N - 1; i++) {
      cache[i * N + i + 1] = std::max(stones[i], stones[i + 1]);
    }

    return solve(stones, N, cache, 0, N - 1);
  }
};
