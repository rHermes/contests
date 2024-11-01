#include <algorithm>
#include <vector>

class Solution
{
public:
  int maxMoves(const std::vector<std::vector<int>>& grid)
  {
    // ok, so we are always moving forwards.
    // This also means that the answer for each grid is set.
    // We can always just start from the back then.
    const int ROWS = grid.size();
    const int COLS = grid[0].size();

    std::vector<int> prev(ROWS, 0);
    std::vector<int> cur(ROWS, 0);

    for (int i = COLS - 2; 0 <= i; i--) {
      // we just need to see what the maximum
      // we can get.
      std::swap(prev, cur);

      cur[0] = 0;
      if (grid[0][i] < grid[0][i + 1]) {
        cur[0] = 1 + prev[0];
      }
      if (grid[0][i] < grid[1][i + 1]) {
        cur[0] = std::max(cur[0], 1 + prev[1]);
      }

      for (int j = 1; j < ROWS - 1; j++) {
        cur[j] = 0;

        const int X = grid[j][i];
        const int U = grid[j - 1][i + 1];
        const int M = grid[j][i + 1];
        const int D = grid[j + 1][i + 1];

        if (X < U) {
          cur[j] = std::max(cur[j], 1 + prev[j - 1]);
        }
        if (X < M) {
          cur[j] = std::max(cur[j], 1 + prev[j]);
        }
        if (X < D) {
          cur[j] = std::max(cur[j], 1 + prev[j + 1]);
        }
      }

      cur[ROWS - 1] = 0;
      if (grid[ROWS - 1][i] < grid[ROWS - 1][i + 1]) {
        cur[ROWS - 1] = 1 + prev[ROWS - 1];
      }
      if (grid[ROWS - 1][i] < grid[ROWS - 2][i + 1]) {
        cur[ROWS - 1] = std::max(cur[ROWS - 1], 1 + prev[ROWS - 2]);
      }
    }

    return std::ranges::max(cur);
  }
};
