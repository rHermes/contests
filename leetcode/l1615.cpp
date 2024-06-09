#include <array>
#include <bitset>
#include <cstdint>
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
  static int maximalNetworkRank(int n, const std::vector<std::vector<int>>& roads)
  {
    std::array<std::uint8_t, 100> conns{};
    std::bitset<100 * 100> connected;

    for (std::size_t i = 0; i < roads.size(); i++) {
      const auto a = roads[i][0];
      const auto b = roads[i][1];

      connected[a * n + b] = true;
      connected[b * n + a] = true;

      conns[a]++;
      conns[b]++;
    }

    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
        const int elems = conns[i] + conns[j] - connected[i * n + j];
        ans = std::max(ans, elems);
      }
    }

    return ans;
  }
};
