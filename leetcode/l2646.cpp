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

  static std::pair<int, int> bestAns(const int N,
                                     const std::vector<std::vector<int>>& G,
                                     const std::vector<int>& prices,
                                     const std::vector<int>& steps,
                                     const int prev,
                                     const int cur)
  {
    int minWith = steps[cur] * prices[cur];
    int minHalf = minWith / 2;

    for (const auto next : G[cur]) {
      if (next == prev)
        continue;

      auto [nextWith, nextHalf] = bestAns(N, G, prices, steps, cur, next);

      minWith = std::min(minWith + nextWith, minWith + nextHalf);
      minHalf = minHalf + nextWith;
    }

    return { minWith, minHalf };
  }

public:
  static int minimumTotalPrice(const int N,
                               std::vector<std::vector<int>>& edges,
                               std::vector<int>& price,
                               std::vector<std::vector<int>>& trips)
  {
    std::vector<std::vector<int>> G(N);
    for (const auto& edge : edges) {
      auto u = edge[0];
      auto v = edge[1];

      G[u].push_back(v);
      G[v].push_back(u);
    }

    // We create a rooted tree at 0. We could do this
    //  more optimally, by picking the center of the tree,
    //  but this will work.

    // Q = cur, parent, level
    std::vector<std::tuple<int, int, int>> Q;
    // parent, level
    std::vector<std::pair<int, int>> tree(N);
    Q.emplace_back(0, -1, 0);
    while (!Q.empty()) {
      const auto [cur, parent, level] = Q.back();
      Q.pop_back();

      tree[cur] = { parent, level };
      for (const auto next : G[cur]) {
        if (next != parent) {
          Q.emplace_back(next, cur, level + 1);
        }
      }
    }

    // we solve each trip, by walking up the rooted tree. First we make sure
    // both nodes are on the same level and then we start walking upwards together.
    std::vector<int> steps(N);
    for (const auto& trip : trips) {
      int tripStart = trip[0];
      int tripEnd = trip[1];

      auto srcLevel = tree[tripStart].second;
      auto dstLevel = tree[tripEnd].second;

      if (srcLevel < dstLevel) {
        std::swap(srcLevel, dstLevel);
        std::swap(tripStart, tripEnd);
      }

      while (dstLevel < srcLevel) {
        steps[tripStart]++;
        tripStart = tree[tripStart].first;
        srcLevel--;
      }

      while (tripStart != tripEnd) {
        steps[tripStart]++;
        steps[tripEnd]++;

        tripStart = tree[tripStart].first;
        tripEnd = tree[tripEnd].first;
      }

      steps[tripStart]++;
    }

    auto hey = bestAns(N, G, price, steps, -1, 0);

    return std::min(hey.first, hey.second);
  }
};

int
main()
{
  return 0;
}
