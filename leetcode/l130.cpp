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
  static void solve(std::vector<std::vector<char>>& board)
  {
    const int ROWS = board.size();
    const int COLS = board[0].size();

    // we just start from the boarders and work our way inwards.
    std::vector<bool> good(ROWS * COLS);

    std::vector<std::pair<int, int>> Q;
    for (int row = 0; row < ROWS; row++) {
      if (board[row][0] == 'O')
        Q.emplace_back(row, 0);

      if (COLS != 1 && board[row][COLS - 1] == 'O')
        Q.emplace_back(row, COLS - 1);
    }

    for (int col = 1; col < COLS - 1; col++) {
      if (board[0][col] == 'O')
        Q.emplace_back(0, col);

      if (ROWS != 1 && board[ROWS - 1][col] == 'O')
        Q.emplace_back(ROWS - 1, col);
    }

    while (!Q.empty()) {
      const auto [y, x] = Q.back();
      Q.pop_back();

      std::initializer_list<std::pair<int, int>> offset{ { -1, 0 }, { 1, 0 }, { 0, 1 }, { 0, -1 } };

      for (const auto& [dy, dx] : offset) {
        int ty = y + dy;
        int tx = x + dx;
        if (1 <= ty && ty < ROWS - 1 && 1 <= tx && tx < COLS - 1 && !good[ty * COLS + tx] && board[ty][tx] == 'O') {
          good[ty * COLS + tx] = true;
          Q.emplace_back(ty, tx);
        }
      }
    }

    for (int row = 1; row < ROWS - 1; row++) {
      for (int col = 1; col < COLS - 1; col++) {
        if (!good[row * COLS + col])
          board[row][col] = 'X';
      }
    }
  }
};

int
main()
{
  return 0;
}
