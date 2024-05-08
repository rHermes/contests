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
  static int shortestPath(const std::vector<std::vector<int>>& grid, int k)
  {
    const int ROWS = grid.size();
    const int COLS = grid[0].size();

    std::vector<int> left(ROWS * COLS, -1);

    std::vector<std::tuple<int, int, int>> Q;
    std::vector<std::tuple<int, int, int>> next;

    const auto addIt = [&](const int y, const int x, const int l) {
      if (l <= left[y * COLS + x])
        return;

      if (grid[y][x]) {
        if (l && left[y * COLS + x] < l - 1)
          next.emplace_back(y, x, l - 1);
      } else {
        next.emplace_back(y, x, l);
      }
    };

    Q.emplace_back(0, 0, k);

    int steps = 0;
    while (!Q.empty()) {
      next.clear();

      for (const auto& [y, x, l] : Q) {
        if (l <= left[y * COLS + x])
          continue;

        left[y * COLS + x] = l;

        if (y == ROWS - 1 && x == COLS - 1)
          return steps;

        if (0 < y)
          addIt(y - 1, x, l);

        if (y < ROWS - 1)
          addIt(y + 1, x, l);

        if (0 < x)
          addIt(y, x - 1, l);

        if (x < COLS - 1)
          addIt(y, x + 1, l);
      }

      std::swap(Q, next);
      steps++;
    }

    return -1;
  }
};

int
main()
{
  return 0;
}
