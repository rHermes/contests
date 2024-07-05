#include <algorithm>
#include <array>
#include <cstdint>
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
  static int maximumScore(const std::vector<int>& scores, const std::vector<std::vector<int>>& edges)
  {
    using UT = std::uint16_t;
    constexpr auto SENTINEL = std::numeric_limits<UT>::max();
    constexpr std::size_t MAXN = 50000;

    const auto N = scores.size();
    if (MAXN < N)
      return -1;

    std::array<std::array<UT, 3>, MAXN> adj;
    std::ranges::fill_n(adj.begin(), N, std::array<UT, 3>{ SENTINEL, SENTINEL, SENTINEL });

    const auto nodeGreater = [&](const UT a, const UT b) {
      if (a == SENTINEL)
        return false;
      if (b == SENTINEL)
        return true;

      return scores[b] < scores[a];
    };

    const auto insertEdge = [&](const UT node, const UT other) {
      // We can actually get away with just two comparisons here, as a
      // binary search.
      auto& q = adj[node];
      if (nodeGreater(other, q[1])) {
        q[2] = q[1];
        if (nodeGreater(other, q[0])) {
          q[1] = q[0];
          q[0] = other;
        } else {
          q[1] = other;
        }
      } else {
        if (nodeGreater(other, q[2])) {
          q[2] = other;
        }
      }
    };

    for (const auto& edge : edges) {
      insertEdge(edge[0], edge[1]);
      insertEdge(edge[1], edge[0]);
    }

    const auto nextSpot = [&](const UT node, const UT filter, UT offset) -> UT {
      for (; offset < 3; offset++) {
        auto ix = adj[node][offset];
        if (ix == SENTINEL)
          break;
        else if (ix != filter)
          return offset;
      }
      return 3;
    };

    int ans = -1;
    for (const auto& edge : edges) {
      const UT i = edge[0];
      const UT j = edge[1];

      auto is = nextSpot(i, j, 0);
      if (is == 3)
        continue;

      auto js = nextSpot(j, i, 0);
      if (js == 3)
        continue;

      auto ia = adj[i][is];
      auto ja = adj[j][js];
      int sum = scores[i] + scores[j] + scores[ia];
      if (ia != ja) {
        sum += scores[ja];
      } else {
        auto ik = nextSpot(i, j, is + 1);
        auto jk = nextSpot(j, i, js + 1);

        constexpr int minScore = std::numeric_limits<int>::lowest();
        const int scoreA = (ik == 3) ? minScore : scores[adj[i][ik]];
        const int scoreB = (jk == 3) ? minScore : scores[adj[j][jk]];

        sum += std::max(scoreA, scoreB);
      }

      ans = std::max(ans, sum);
    }

    return ans;
  }
};
