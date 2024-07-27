#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <limits>
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
  static constexpr long long minimumCost(const std::string& source,
                                         const std::string& target,
                                         const std::vector<char>& original,
                                         const std::vector<char>& changed,
                                         const std::vector<int>& cost)
  {
    constexpr int SENTINEL = std::numeric_limits<int>::max();

    std::array<int, 26 * 26> dist;
    std::ranges::fill(dist, SENTINEL);
    for (int i = 0; i < 26; i++) {
      dist[i * 26 + i] = 0;
    }

    const int N = source.size();
    const int M = original.size();
    for (int i = 0; i < M; i++) {
      const auto src = original[i] - 'a';
      const auto dst = changed[i] - 'a';
      const auto grp = cost[i];
      dist[src * 26 + dst] = std::min(grp, dist[src * 26 + dst]);
    }

    // Calculate the shortest path between all pairs.
    for (int k = 0; k < 26; k++) {
      for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
          auto& distij = dist[i * 26 + j];
          const std::int64_t altDist = static_cast<std::int64_t>(dist[i * 26 + k]) + dist[k * 26 + j];
          if (altDist < distij) {
            distij = altDist;
          }
        }
      }
    }

    // Now we know the path, let's see if we can get the cost.
    std::int64_t ans = 0;
    for (int i = 0; i < N; i++) {
      const int src = source[i] - 'a';
      const int dst = target[i] - 'a';
      const auto d = dist[src * 26 + dst];

      if (d == SENTINEL) {
        return -1;
      }
      ans += d;
    }

    return ans;
  }
};
