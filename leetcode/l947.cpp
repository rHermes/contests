#include <array>
#include <cstdint>
#include <iostream>
#include <utility>
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
  static constexpr int removeStones(const std::vector<std::vector<int>>& stones)
  {
    constexpr int MAXX = 10001;

    // 0 here means we are unconnected, it's used to signal that we are
    // creating a new component.
    std::array<std::uint16_t, 2 * MAXX + 1> parents{};
    std::array<unsigned char, 2 * MAXX + 1> ranks{};

    int components = 0;
    const auto getParent = [&](const int a) {
      int root = parents[a];
      if (root == 0) {
        components++;
        parents[a] = a;
        return a;
      }

      while (root != parents[root]) {
        root = parents[root];
      }

      int cur = a;
      while (root != parents[cur]) {
        cur = std::exchange(parents[cur], root);
      }
      return root;
    };

    const auto merge = [&](int a, int b) {
      a = getParent(a);
      b = getParent(b);

      if (a == b) {
        return;
      }

      components--;

      if (ranks[a] < ranks[b])
        std::swap(a, b);

      parents[b] = a;
      if (ranks[a] == ranks[b])
        ranks[a]++;
    };

    for (const auto& stone : stones) {
      const int x = 1 + stone[0];
      const int y = 1 + stone[1] + MAXX;

      merge(x, y);
    }

    return stones.size() - components;
  }
};
