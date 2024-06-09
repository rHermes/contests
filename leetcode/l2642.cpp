#include <iostream>
#include <limits>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Graph
{
  int N;
  std::vector<int> dist;
  static constexpr int sentinel = std::numeric_limits<int>::max();

public:
  Graph(int n, const std::vector<std::vector<int>>& edges) : N{ n }, dist(N * N, sentinel)
  {
    for (int i = 0; i < n; i++) {
      dist[i * N + i] = 0;
    }
    for (const auto& edge : edges) {
      addEdge(edge);
    }
  }

  void addEdge(const std::vector<int>& edge)
  {
    const auto from = edge[0];
    const auto to = edge[1];
    const auto cost = edge[2];

    if (dist[from * N + to] <= cost)
      return;

    dist[from * N + to] = cost;

    // Update from me and out
    for (int i = 0; i < N; i++) {
      const auto d1 = dist[(i * N) + from];
      if (d1 == sentinel)
        continue;

      for (int j = 0; j < N; j++) {
        const auto d2 = dist[(to * N) + j];
        if (d2 == sentinel)
          continue;

        dist[(i * N) + j] = std::min(dist[(i * N) + j], d1 + d2 + cost);
      }
    }
  }

  int shortestPath(int node1, int node2) const
  {
    const auto d = dist[node1 * N + node2];
    if (d != sentinel)
      return d;
    else
      return -1;
  }
};
