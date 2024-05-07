#include <iostream>
#include <queue>
#include <vector>

class Solution
{
public:
  std::vector<int> findMinHeightTrees(int n, std::vector<std::vector<int>>& edges)
  {
    if (n == 1)
      return { 0 };

    std::vector<int> G(n);
    std::vector<int> connections(n);

    for (const auto& edge : edges) {
      G[edge[0]] ^= edge[1];
      G[edge[1]] ^= edge[0];
      connections[edge[0]]++;
      connections[edge[1]]++;
    }

    std::queue<int> Q;
    for (std::size_t i = 0; i < static_cast<size_t>(n); i++) {
      if (connections[i] == 1) {
	Q.push(i);
      }
    }

    std::vector<int> ans;
    while (!Q.empty()) {
      ans.clear();

      auto left = Q.size();
      while (0 < left) {
	const auto node = Q.front();
	Q.pop();
	left--;

	ans.push_back(node);
	const auto next = G[node];
	G[next] ^= node;

	if (--connections[next] == 1) {
	  Q.push(next);
	}
      }
    }

    return ans;
  }
};

static auto _ = []() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

int
main()
{
}
