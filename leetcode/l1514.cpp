#include <iostream>
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
  static double maxProbability(const int N,
                               const std::vector<std::vector<int>>& edges,
                               const std::vector<double>& succProb,
                               const int start_node,
                               const int end_node)
  {
    // Since the probability can only shrink, it means that we can use a shortest
    // path algorithm like dijekstra to solve this.
    std::vector<std::vector<std::pair<int, double>>> graph(N);

    const int EN = edges.size();
    for (int i = 0; i < EN; i++) {
      const auto a = edges[i][0];
      const auto b = edges[i][1];
      const auto w = succProb[i];

      graph[a].emplace_back(b, w);
      graph[b].emplace_back(a, w);
    }

    std::vector<double> bestProb(N, 0);

    std::priority_queue<std::pair<double, int>> Q;
    Q.emplace(1, start_node);

    while (!Q.empty()) {
      const auto [curW, curIdx] = Q.top();
      Q.pop();

      if (curW < bestProb[curIdx])
        continue;

      if (curIdx == end_node) {
        return curW;
      }

      for (const auto& [nextIdx, nextP] : graph[curIdx]) {
        const double nextW = curW * nextP;

        if (bestProb[nextIdx] < nextW) {
          bestProb[nextIdx] = nextW;
          Q.emplace(nextW, nextIdx);
        }
      }
    }

    return 0;
  }
};
