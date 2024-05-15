#include <deque>
#include <iostream>
#include <queue>
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
  static int maximumSafenessFactor(std::vector<std::vector<int>>& grid)
  {
    const int N = grid.size();

    // We first paint the grid with the distance to the nearest
    // thief, using a sort of floodfill.
    std::deque<std::tuple<int, int, int>> pos;
    for (int row = 0; row < N; row++) {
      for (int col = 0; col < N; col++) {
        if (grid[row][col] == 1) {
          pos.emplace_back(1, row, col);
        }
      }
    }

    while (!pos.empty()) {
      const auto [score, row, col] = pos.front();
      pos.pop_front();

      if (1 < grid[row][col])
        continue;

      grid[row][col] = score;

      if (0 < row && grid[row - 1][col] == 0) {
        pos.emplace_back(score + 1, row - 1, col);
      }

      if (row < N - 1 && grid[row + 1][col] == 0) {
        pos.emplace_back(score + 1, row + 1, col);
      }

      if (0 < col && grid[row][col - 1] == 0) {
        pos.emplace_back(score + 1, row, col - 1);
      }

      if (col < N - 1 && grid[row][col + 1] == 0) {
        pos.emplace_back(score + 1, row, col + 1);
      }
    }

    // Now that we have the board all setup, we are just going to do a
    // A* like seutp.
    std::priority_queue<std::tuple<int, int, int, int>> Q;
    Q.emplace(grid[0][0], -(N * N), 0, 0);

    while (!Q.empty()) {
      const auto [score, _, row, col] = Q.top();
      Q.pop();

      if (grid[row][col] == 0)
        continue;
      grid[row][col] = 0;

      if (row == N - 1 && col == N - 1) {
        return score - 1;
      }

      if (col < N - 1 && grid[row][col + 1] != 0) {
        Q.emplace(std::min(score, grid[row][col + 1]), -(N - row + N - col - 1), row, col + 1);
      }

      if (row < N - 1 && grid[row + 1][col] != 0) {
        Q.emplace(std::min(score, grid[row + 1][col]), -(N - row - 1 + N - col), row + 1, col);
      }

      if (0 < col && grid[row][col - 1] != 0) {
        Q.emplace(std::min(score, grid[row][col - 1]), -(N - row + N - col + 1), row, col - 1);
      }

      if (0 < row && grid[row - 1][col] != 0) {
        Q.emplace(std::min(score, grid[row - 1][col]), -(N - row + 1 + N - col), row - 1, col);
      }
    }

    return 0;
  }
};

int
main()
{
  return 0;
}
