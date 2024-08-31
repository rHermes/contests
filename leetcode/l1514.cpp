#include <iostream>
#include <memory>
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
    // We avoid building a graph here, to minimize the overall cost.
    auto prob = std::make_unique<double[]>(N);
    prob[start_node] = 1.0;

    const int SN = edges.size();
    for (int i = 0; i < N; i++) {
      bool connected = false;
      for (int j = 0; j < SN; j++) {
        const int a = edges[j][0];
        const int b = edges[j][1];
        const double p = succProb[j];

        if (prob[b] < prob[a] * p) {
          prob[b] = prob[a] * p;
          connected = true;
        }

        if (prob[a] < prob[b] * p) {
          prob[a] = prob[b] * p;
          connected = true;
        }
      }

      if (!connected)
        break;
    }
    return prob[end_node];
  }
};
