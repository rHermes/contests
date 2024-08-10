#include <algorithm>
#include <array>
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
  static constexpr std::array<std::uint64_t, 8> sigs{ 10579416120, 11080644120, 18129162870, 19632846870,
                                                      26180137620, 27683821620, 34732340370, 35233568370 };

public:
  static constexpr int numMagicSquaresInside(const std::vector<std::vector<int>>& grid)
  {
    const int ROWS = grid.size();
    const int COLS = grid.size();

    // This is lame. We are only looking for normal magic squares and there
    // are only 8 of those. I precomputed these and stored their signatures
    // in an array.
    int ans = 0;
    for (int y = 0; y < ROWS - 2; y++) {
      for (int x = 0; x < COLS - 2; x++) {
        if (grid[y + 1][x + 1] != 5)
          continue;

        std::uint64_t sig = 0;
        for (int dy = 0; dy < 3; dy++) {
          for (int dx = 0; dx < 3; dx++) {
            sig <<= 4;
            sig |= grid[y + dy][x + dx];
          }
        }

        if (std::ranges::binary_search(sigs, sig)) {
          // A magic square cannot be right next to another one, so we can skip.
          x++;
          ans++;
        };
      }
    }

    return ans;
  }
};
