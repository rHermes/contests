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
  static constexpr int maxDistance(std::vector<std::vector<int>>& grid)
  {
    const int ROWS = grid.size();
    const int COLS = grid[0].size();

    constexpr int MAX_DIST = 201;

    for (int y = 0; y < ROWS; y++) {
      for (int x = 0; x < COLS; x++) {
        auto& square = grid[y][x];
        if (square == 1)
          continue;

        square = MAX_DIST;
        if (0 < y)
          square = std::min(square, 1 + grid[y - 1][x]);

        if (0 < x)
          square = std::min(square, 1 + grid[y][x - 1]);
      }
    }

    int ans = 0;

    for (int y = ROWS - 1; 0 <= y; y--) {
      for (int x = COLS - 1; 0 <= x; x--) {
        auto& square = grid[y][x];
        if (square == 1)
          continue;

        if (y < ROWS - 1)
          square = std::min(square, 1 + grid[y + 1][x]);

        if (x < COLS - 1)
          square = std::min(square, 1 + grid[y][x + 1]);

        ans = std::max(ans, square);
      }
    }

    if (ans == MAX_DIST)
      return -1;

    return ans - 1;
  }
};
