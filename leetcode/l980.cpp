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
  static int goodPaths(std::vector<std::vector<int>>& grid,
                       const int ROWS,
                       const int COLS,
                       const int stepsLeft,
                       const int y,
                       const int x)
  {
    if (y < 0 || ROWS <= y || x < 0 || COLS <= x || grid[y][x] == -1)
      return 0;

    if (grid[y][x] == 2) {
      return stepsLeft == 0;
    }

    if (stepsLeft == 0) {
      return false;
    }

    int ans = 0;
    auto prev = std::exchange(grid[y][x], -1);

    ans += goodPaths(grid, ROWS, COLS, stepsLeft - 1, y, x + 1);
    ans += goodPaths(grid, ROWS, COLS, stepsLeft - 1, y, x - 1);
    ans += goodPaths(grid, ROWS, COLS, stepsLeft - 1, y + 1, x);
    ans += goodPaths(grid, ROWS, COLS, stepsLeft - 1, y - 1, x);

    grid[y][x] = prev;

    return ans;
  }

public:
  static int uniquePathsIII(std::vector<std::vector<int>>& grid)
  {
    const int ROWS = grid.size();
    const int COLS = grid[0].size();

    // This is going to be a simple task.
    std::pair<int, int> start;
    int open = 0;
    for (int row = 0; row < ROWS; row++) {
      for (int col = 0; col < COLS; col++) {
        if (grid[row][col] != -1) {
          open++;
        }

        if (grid[row][col] == 1) {
          start = { row, col };
        }
      }
    }

    return goodPaths(grid, ROWS, COLS, open - 1, start.first, start.second);
  }
};
