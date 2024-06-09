#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
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
  static int minCost(const int maxTime, const std::vector<std::vector<int>>& edges, const std::vector<int>& passingFees)
  {
    const int N = passingFees.size();

    std::vector<std::unordered_map<int, int>> G(N);

    for (const auto& edge : edges) {
      auto [it, inserted] = G[edge[0]].emplace(edge[1], edge[2]);
      if (!inserted) {
        if (it->second <= edge[2]) {
          continue;
        }

        it->second = edge[2];
      }

      G[edge[1]][edge[0]] = edge[2];
    }

    // SCORE, TIME, POS
    using T = std::tuple<int, int, int>;
    std::priority_queue<T, std::vector<T>, std::ranges::greater> Q;

    std::vector<int> dist(N, maxTime + 1);
    std::vector<int> cost(N, std::numeric_limits<int>::max());

    dist[0] = 0;
    cost[0] = passingFees[0];
    Q.emplace(passingFees[0], dist[0], 0);

    while (!Q.empty()) {
      const auto [score, time, pos] = Q.top();
      Q.pop();

      if (pos == N - 1) {
        return score;
      }

      if (cost[pos] < score && dist[pos] < time)
        continue;

      for (const auto& [dst, timeCost] : G[pos]) {
        const auto newTime = timeCost + time;
        if (maxTime < newTime)
          continue;

        const auto newScore = score + passingFees[dst];
        if (newScore < cost[dst]) {
          cost[dst] = newScore;
          dist[dst] = newTime;
          Q.emplace(newScore, newTime, dst);
        } else if (newTime < dist[dst]) {
          dist[dst] = newTime;
          Q.emplace(newScore, newTime, dst);
        }
      }
    }

    return -1;
  }
};
