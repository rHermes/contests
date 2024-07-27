#include <algorithm>
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
  static int findTheCity(const int N, const std::vector<std::vector<int>>& edges, const int distanceThreshold)
  {
    std::vector<int> dist(N * N, std::numeric_limits<int>::max());
    for (const auto& edge : edges) {
      const auto a = edge[0];
      const auto b = edge[1];
      const auto w = edge[2];
      dist[a * N + b] = w;
      dist[b * N + a] = w;
    }

    for (int i = 0; i < N; i++) {
      dist[i * N + i] = 0;
    }

    for (int k = 0; k < N; k++) {
      for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
          auto& distij = dist[i * N + j];
          const std::int64_t newDist = static_cast<std::int64_t>(dist[i * N + k]) + dist[k * N + j];
          if (newDist < distij) {
            distij = newDist;
            dist[j * N + i] = newDist;
          }
        }
      }
    }

    // We just register how many edges each node has in this new graph.
    std::vector<int> adj(N, 0);
    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        if (dist[i * N + j] <= distanceThreshold) {
          adj[i]++;
          adj[j]++;
        }
      }
    }

    // We are looking for the minimnal element from the back
    // so we need to look in the reverse order, since min_element
    // returns the first minimal object it finds.
    const auto rmin = std::min_element(adj.rbegin(), adj.rend());
    const auto fromBack = std::distance(adj.rbegin(), rmin);
    return N - fromBack - 1;
  }
};
