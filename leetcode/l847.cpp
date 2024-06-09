#include <cstdint>
#include <deque>
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
public:
  static int shortestPathLength(const std::vector<std::vector<int>>& graph)
  {
    const int N = graph.size();

    using T = std::uint16_t;
    const T finalDest = (1 << N) - 1;
    const int ROW = finalDest + 1;

    std::vector<bool> seen(N * ROW);
    std::deque<std::pair<int, T>> Q;

    for (int i = 0; i < N; i++) {
      T good = 1 << i;
      seen[i * N + good] = true;
      Q.emplace_back(i, good);
    }

    int wave = 0;
    while (!Q.empty()) {
      const int thisWave = Q.size();
      for (int i = 0; i < thisWave; i++) {
        auto [curPos, cur] = Q.front();
        Q.pop_front();

        if (cur == finalDest)
          return wave;

        for (const auto next : graph[curPos]) {
          const T nex = cur | (1 << next);
          const int key = next * ROW + nex;
          if (seen[key])
            continue;

          seen[key] = true;
          Q.emplace_back(next, nex);
        }
      }
      // std::cout << "Next wave!\n";
      wave++;
    }

    return -1;
  }
};
