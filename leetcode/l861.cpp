#include <vector>

class Solution
{
public:
  static int matrixScore(std::vector<std::vector<int>>& grid)
  {
    const auto ROWS = grid.size();
    const auto COLS = grid[0].size();

    const auto flipRow = [&](const std::size_t row) {
      for (std::size_t col = 0; col < COLS; col++)
        grid[row][col] = grid[row][col] == 0;
    };

    // We maximize each number, by making sure the first bit is 1.
    // We then compress these rows into the first one, as we only need
    // to know the number of ones in order to make the decision to flip or not.
    for (std::size_t row = 0; row < ROWS; row++) {
      if (!grid[row][0]) {
        flipRow(row);
      }

      if (0 < row) {
        for (std::size_t col = 0; col < COLS; col++) {
          grid[0][col] += grid[row][col];
        }
      }
    }

    const int lim = ROWS / 2;

    int ans = 0;
    for (std::size_t col = 0; col < COLS; col++) {
      ans <<= 1;
      if (grid[0][col] <= lim) {
        ans += ROWS - grid[0][col];
      } else {
        ans += grid[0][col];
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
