#include <iostream>
#include <vector>

static auto _ = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return nullptr;
}();

class Solution
{
private:
  using Graph = std::vector<std::vector<int>>;

  Graph G;
  int N;

  std::vector<int> pathSums;
  std::vector<int> children;

  void dfsPathSum(const int prev, const int cur)
  {
    children[cur] = 1;

    int sum = 0;
    for (const auto next : G[cur]) {
      if (next == prev)
	continue;

      dfsPathSum(cur, next);

      sum += pathSums[next];
      children[cur] += children[next];
    }

    pathSums[cur] = sum + children[cur] - 1;
  }

  void dfsReroot(const int prev, const int cur)
  {
    // we skip the initial reroot, since we already have the solution.
    if (cur != prev) {
      pathSums[cur] = pathSums[prev] - children[cur] + (N - children[cur]);
    }

    for (const auto next : G[cur]) {
      if (next == prev)
	continue;

      dfsReroot(cur, next);
    }
  }

public:
  std::vector<int> sumOfDistancesInTree(int n, std::vector<std::vector<int>>& edges)
  {
    if (n == 1) {
      return { 0 };
    } else if (n == 2) {
      return { 1, 1 };
    }

    this->N = n;
    pathSums.resize(N);
    children.resize(N);

    G.clear();
    G.resize(N);

    for (const auto& edge : edges) {
      G[edge[0]].push_back(edge[1]);
      G[edge[1]].push_back(edge[0]);
    }

    const int r0 = 0;

    // and we update the arrays
    dfsPathSum(r0, r0);
    dfsReroot(r0, r0);

    return pathSums;
  }
};

int
main()
{
  return 0;
}
