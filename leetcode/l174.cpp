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
  static constexpr int calculateMinimumHP(std::vector<std::vector<int>>& grid)
  {
    const int ROWS = grid.size();
    const int COLS = grid.front().size();

    // Floor
    grid[ROWS - 1][COLS - 1] = std::max(1, 1 - grid[ROWS - 1][COLS - 1]);
    for (int i = COLS - 2; 0 <= i; i--) {
      grid[ROWS - 1][i] = std::max(1, grid[ROWS - 1][i + 1] - grid[ROWS - 1][i]);
    }

    // Rest of the tiles
    for (int row = ROWS - 2; 0 <= row; row--) {
      grid[row][COLS - 1] = std::max(1, grid[row + 1][COLS - 1] - grid[row][COLS - 1]);
      for (int col = COLS - 2; 0 <= col; col--) {
        const auto nextReq = std::min(grid[row + 1][col], grid[row][col + 1]);
        grid[row][col] = std::max(1, nextReq - grid[row][col]);
      }
    }

    return grid[0][0];
  }
};
