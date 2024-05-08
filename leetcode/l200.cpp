#include <iostream>
#include <vector>

static auto _ = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return nullptr;
}();

class Solution
{
public:
  static int numIslands(std::vector<std::vector<char>>& grid)
  {
    const std::size_t M = grid.size();
    const std::size_t N = grid[0].size();

    int ans = 0;

    // we reuse the queues to minimize queues.
    std::vector<std::pair<std::size_t, std::size_t>> Q;

    for (std::size_t origY = 0; origY < M; origY++) {
      for (std::size_t origX = 0; origX < N; origX++) {
        if (grid[origY][origX] == '0')
          continue;

        grid[origY][origX] = '0';

        ans++;

        Q.clear();
        Q.emplace_back(origY, origX);

        while (!Q.empty()) {
          const auto [y, x] = Q.back();
          Q.pop_back();

          if (0 < y && grid[y - 1][x] == '1') {
            grid[y - 1][x] = '0';
            Q.emplace_back(y - 1, x);
          }

          if (y < M - 1 && grid[y + 1][x] == '1') {
            grid[y + 1][x] = '0';
            Q.emplace_back(y + 1, x);
          }

          if (0 < x && grid[y][x - 1] == '1') {
            grid[y][x - 1] = '0';
            Q.emplace_back(y, x - 1);
          }

          if (x < N - 1 && grid[y][x + 1] == '1') {
            grid[y][x + 1] = '0';
            Q.emplace_back(y, x + 1);
          }
        }
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
