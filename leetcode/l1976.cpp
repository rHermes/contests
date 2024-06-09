#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
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
  static int countPaths(int N, const std::vector<std::vector<int>>& roads)
  {
    using HH = std::int64_t;
    constexpr int MODN = 1000000007;
    std::vector<std::vector<std::pair<int, int>>> G(N);

    for (const auto& road : roads) {
      const auto& a = road[0];
      const auto& b = road[1];
      const auto& c = road[2];

      G[a].emplace_back(b, c);
      G[b].emplace_back(a, c);
    }

    // time, pos
    std::vector<int> ways(N, 0);
    std::vector<HH> dist(N, std::numeric_limits<HH>::max());

    dist[0] = 0;
    ways[0] = 1;

    using T = std::pair<HH, int>;
    std::priority_queue<T, std::vector<T>, std::ranges::greater> Q;
    Q.emplace(0, 0);

    while (!Q.empty()) {
      const auto [time, cur] = Q.top();
      Q.pop();

      if (dist[cur] < time) {
        continue;
      }

      // ok, at this time, there are some ways.
      if (cur == N - 1) {
        break;
      }

      const int way = ways[cur];

      for (const auto& [next, cost] : G[cur]) {
        HH nextCost = cost + time;

        if (nextCost < dist[next]) {
          ways[next] = way;
          dist[next] = nextCost;
          Q.emplace(nextCost, next);
        } else if (nextCost == dist[next])
          ways[next] = (ways[next] + way) % MODN;
      }
    }

    return ways[N - 1];
  }
};
