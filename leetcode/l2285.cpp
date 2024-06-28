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
public:
  static long long maximumImportance(int n, const std::vector<std::vector<int>>& roads)
  {
    std::vector<int> adj(n);
    for (const auto& road : roads) {
      ++adj[road[0]];
      ++adj[road[1]];
    }

    std::ranges::sort(adj);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
      long long a = adj[i];
      ans += a * (i + 1);
    }

    return ans;
  }
};
