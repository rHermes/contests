#include <algorithm>
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
  using OUT = std::vector<std::vector<int>>;

public:
  static OUT getAncestors(int n, const OUT& edges)
  {
    OUT G(n);
    std::vector<int> adj(n);

    for (const auto& edge : edges) {
      G[edge[0]].push_back(edge[1]);
      adj[edge[1]]++;
    }

    for (auto& adj : G)
      std::ranges::sort(adj);

    std::vector<int> Q;
    for (int i = 0; i < n; i++) {
      if (adj[i] == 0)
        Q.push_back(i);
    }

    OUT out(n);

    while (!Q.empty()) {
      const auto cur = Q.back();
      Q.pop_back();

      {
        std::ranges::sort(out[cur]);
        auto [first, last] = std::ranges::unique(out[cur]);
        out[cur].erase(first, last);
      }
      for (const auto next : G[cur]) {
        out[next].push_back(cur);
        out[next].insert(out[next].end(), out[cur].begin(), out[cur].end());
        if (--adj[next] == 0) {
          Q.push_back(next);
        }
      }
    }

    return out;
  }
};
