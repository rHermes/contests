#include <iostream>
#include <numeric>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  using CACHE = std::vector<int>;

  static int solve(const std::vector<int>& piles,
                   const int N,
                   CACHE& cache,
                   const int M,
                   const int offset,
                   const int totalLeft)
  {
    if (offset == N)
      return 0;

    // totalLeft, is really a function of offset, but it's easier for us if we just keep it simple.
    const int key = offset * (N + 1) + M;
    if (-1 < cache[key])
      return cache[key];

    // Ok, so we are just going to simulate every single move.
    int takenSoFar = 0;
    int best = 0;

    for (int x = 0; x < 2 * M; x++) {
      const int pos = offset + x;
      if (N <= pos)
        break;

      takenSoFar += piles[pos];

      // Now what the other person can get at best here is:
      const int otherGets = solve(piles, N, cache, std::max(x + 1, M), pos + 1, totalLeft - takenSoFar);
      const int weGet = (totalLeft - takenSoFar) - otherGets;

      best = std::max(best, weGet + takenSoFar);
    }

    cache[key] = best;
    return best;
  }

public:
  static int stoneGameII(const std::vector<int>& piles)
  {
    const int N = piles.size();
    const int totalStones = std::reduce(piles.begin(), piles.end(), 0);

    CACHE cache(N * (N + 1), -1);

    return solve(piles, N, cache, 1, 0, totalStones);
  }
};
