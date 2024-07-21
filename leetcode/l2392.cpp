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
  static std::vector<int> topoSort(const int k, const std::vector<std::vector<int>>& conditions)
  {
    std::vector<std::vector<int>> outEdges(k);
    std::vector<int> links(k, 0);

    for (const auto& edge : conditions) {
      const auto src = edge[0] - 1;
      const auto dst = edge[1] - 1;
      outEdges[src].push_back(dst);
      links[dst]++;
    }

    std::vector<int> Q;
    for (int i = 0; i < k; i++) {
      if (links[i] == 0) {
        Q.push_back(i);
      }
    }

    std::vector<int> order;
    order.reserve(k);
    while (!Q.empty()) {
      const auto cur = Q.back();
      Q.pop_back();

      order.push_back(cur);

      for (const auto next : outEdges[cur]) {
        if (--links[next] == 0) {
          Q.push_back(next);
        }
      }
    }

    return order;
  }

public:
  static std::vector<std::vector<int>> buildMatrix(const int k,
                                                   const std::vector<std::vector<int>>& rowConditions,
                                                   const std::vector<std::vector<int>>& colConditions)
  {
    // The big clue here is that the two axis are totally independent, so it's
    // enough to find a solution that works for each axis and just combine them.
    // To do this, we use a topological sort.
    const auto rowOrder = topoSort(k, rowConditions);
    if (static_cast<int>(rowOrder.size()) != k)
      return {};

    const auto colOrder = topoSort(k, colConditions);
    if (static_cast<int>(colOrder.size()) != k)
      return {};

    std::vector<std::pair<int, int>> placements(k);
    for (int i = 0; i < k; i++) {
      placements[rowOrder[i]].first = i;
      placements[colOrder[i]].second = i;
    }

    std::vector<std::vector<int>> out(k, std::vector<int>(k, 0));
    for (int i = 0; i < k; i++) {
      const auto [row, col] = placements[i];
      out[row][col] = i + 1;
    }

    return out;
  }
};
