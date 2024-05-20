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
  using G = std::vector<std::vector<int>>;

  static int checkIfNoZeros(const G& grid, int ROWS, int COLS)
  {
    int ans = 0;
    for (int row = 0; row < ROWS; row++) {
      for (int col = 0; col < COLS; col++) {
        if (grid[row][col] == 0)
          return 0;
        else
          ans += grid[row][col];
      }
    }

    return ans;
  }

  static void dfs(G& grid, const int ROWS, const int COLS, const int row, const int col, const int count, int& ans)
  {

    if (ROWS <= row || row < 0 || COLS <= col || col < 0 || !grid[row][col])
      return;

    int tmp = grid[row][col];
    ans = std::max(ans, count + tmp);

    grid[row][col] = 0;

    dfs(grid, ROWS, COLS, row - 1, col, count + tmp, ans);
    dfs(grid, ROWS, COLS, row + 1, col, count + tmp, ans);
    dfs(grid, ROWS, COLS, row, col - 1, count + tmp, ans);
    dfs(grid, ROWS, COLS, row, col + 1, count + tmp, ans);

    grid[row][col] = tmp;
  }

public:
  static int getMaximumGold(G& grid)
  {
    const int ROWS = grid.size();
    const int COLS = grid[0].size();

    // we check if the grid is all zeros.
    const int totalSum = checkIfNoZeros(grid, ROWS, COLS);
    if (totalSum)
      return totalSum;

    int ans = 0;
    for (int row = 0; row < ROWS; row++) {
      for (int col = 0; col < COLS; col++) {
        if (grid[row][col])
          dfs(grid, ROWS, COLS, row, col, 0, ans);
      }
    }

    return ans;
  }
};

int
main()
{
  return 0;
}
