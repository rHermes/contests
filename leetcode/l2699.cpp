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
  static constexpr int MAX = 2000000001;
  struct Node
  {
    int cost;
    int idx;

    constexpr auto operator<=>(const Node& other) const
    {
      if (auto cmp = other.cost <=> cost; cmp != 0) {
        return cmp;
      }
      return other.idx <=> idx;
    }
  };

  using GRAPH = std::vector<std::unordered_map<int, int>>;

  // Cost, specials, path
  static int shortestPath(const GRAPH& G, const int src, const int dst, const int limit)
  {
    const int N = G.size();
    std::vector<int> dist(N, std::numeric_limits<int>::max());
    std::priority_queue<Node> Q;
    dist[src] = 0;
    Q.emplace(0, src);

    while (!Q.empty()) {
      const auto cur = Q.top();
      Q.pop();

      if (limit < cur.cost || dist[cur.idx] < cur.cost)
        continue;

      if (cur.idx == dst) {
        return cur.cost;
      }

      for (const auto& [next, cost] : G[cur.idx]) {
        const auto nextCost = cost + cur.cost;
        if (nextCost < dist[next]) {
          dist[next] = nextCost;
          Q.emplace(nextCost, next);
        }
      }
    }

    return MAX;
  }

public:
  static std::vector<std::vector<int>> modifiedGraphEdges(const int N,
                                                          std::vector<std::vector<int>>& edges,
                                                          const int source,
                                                          const int destination,
                                                          const int target)
  {

    GRAPH G(N);
    for (const auto& edge : edges) {
      const auto a = edge[0];
      const auto b = edge[1];
      const auto w = edge[2];

      if (w != -1) {
        G[a].emplace(b, w);
        G[b].emplace(a, w);
      }
    }

    int currentShortestDistance = shortestPath(G, source, destination, target);
    if (currentShortestDistance < target) {
      return {};
    }

    bool matchesTarget = (currentShortestDistance == target);

    // Ok, we now iteratore through the edges and try to adjust them.
    for (auto& edge : edges) {
      const auto a = edge[0];
      const auto b = edge[1];
      auto w = edge[2];

      if (w != -1) {
        continue;
      }

      // If we are already good, we are just shutting of the other parts.
      if (matchesTarget) {
        edge[2] = MAX - 1;
        continue;
      }

      edge[2] = 1;
      // Ok, so either we just set it to zero.
      G[a].emplace(b, 1);
      G[b].emplace(a, 1);

      int newDistance = shortestPath(G, source, destination, target);

      // If the we are below, we know it might be poossible.
      if (newDistance <= target) {
        matchesTarget = true;
        edge[2] += target - newDistance;
      }
    }

    // If we match the target, we return this.
    if (matchesTarget) {
      return edges;
    } else {
      return {};
    }
  }
};
