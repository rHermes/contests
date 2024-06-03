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
  static bool canFinish(int N, const std::vector<std::vector<int>>& prerequisites)
  {

    // So this is basically just a loop check.
    std::vector<int> conns(N, 0);
    std::vector<std::vector<int>> G(N);

    for (const auto& preq : prerequisites) {
      const auto& src = preq[0];
      const auto& dst = preq[1];
      conns[dst]++;
      G[src].push_back(dst);
    }

    std::vector<int> topo;
    for (int i = 0; i < N; i++) {
      if (conns[i] == 0) {
        topo.push_back(i);
      }
    }

    int done = 0;
    while (!topo.empty()) {
      auto cur = topo.back();
      topo.pop_back();

      done++;

      for (const auto next : G[cur]) {
        if (--conns[next] == 0) {
          topo.push_back(next);
        }
      }
    }

    return done == N;
  }
};

int
main()
{
  return 0;
}
