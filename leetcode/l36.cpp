#include <array>
#include <iostream>
#include <vector>

class Solution
{
public:
  static bool isValidSudoku(std::vector<std::vector<char>>& board)
  {
    std::array<bool, 9 * 9> rows{};
    std::array<bool, 9 * 9> cols{};
    std::array<bool, 9 * 9> groups{};

    for (int y = 0; y < 9; y++) {
      for (int x = 0; x < 9; x++) {
        if (board[y][x] == '.')
          continue;

        const int c = board[y][x] - '1';

        if (rows[y * 9 + c])
          return false;
        rows[y * 9 + c] = true;

        if (cols[x * 9 + c])
          return false;
        cols[x * 9 + c] = true;

        const int groupY = y / 3;
        const int groupX = x / 3;

        if (groups[(groupY * 3 + groupX) * 9 + c])
          return false;
        groups[(groupY * 3 + groupX) * 9 + c] = true;
      }
    }

    return true;
  }
};

static auto _ = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return nullptr;
}();
