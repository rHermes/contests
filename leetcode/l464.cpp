#include <bitset>
#include <cstdint>

class Solution
{
  using UT = std::uint32_t;
  using BT = std::bitset<1 << 20>;

  bool solve(const int goal, const int limit, BT& cache, BT& visited, const UT state, int sum)
  {
    visited[state] = true;

    if (goal <= sum) {
      return false;
    }

    for (int i = 0; i < limit; i++) {
      if (state & (1 << i)) {
        continue;
      }

      const auto next = state | (1 << i);
      auto ans = false;
      if (visited[next])
        ans = cache[next];
      else
        ans = solve(goal, limit, cache, visited, next, sum + i + 1);

      if (!ans) {
        cache[state] = true;
        return true;
      }
    }

    return false;
  }

public:
  bool canIWin(const int K, const int N)
  {
    if (N == 0)
      return true;

    if ((K * (K + 1)) / 2 < N)
      return false;

    BT cache;
    BT visited;
    return solve(N, K, cache, visited, 0, 0);
  }
};
