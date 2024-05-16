#include <bitset>
#include <iostream>
#include <string>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  static constexpr int MAX_SIZE = 9;
  static void solve(const int n,
                    std::vector<std::vector<std::string>>& outs,
                    std::bitset<MAX_SIZE * MAX_SIZE> board,
                    const int row)
  {
    if (row == n) {
      // this means we are good, we will now append.
      std::vector<std::string> bard(n, std::string(n, '.'));

      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (!board[i * MAX_SIZE + j]) {
            bard[i][j] = 'Q';
            break;
          }
        }
      }

      outs.emplace_back(std::move(bard));
      return;
    }

    auto filledPrev = board;
    for (int i = 0; i < n; i++)
      filledPrev[row * MAX_SIZE + i] = true;

    for (int i = 0; i < n; i++) {
      if (board[row * MAX_SIZE + i])
        continue;

      auto cur = filledPrev;
      cur[row * MAX_SIZE + i] = false;
      // ok, now we just mark the two sides to the left of it.
      for (int rr = row + 1; rr < n; rr++) {
        cur[rr * MAX_SIZE + i] = true;

        if (i + (rr - row) < n)
          cur[rr * MAX_SIZE + i + (rr - row)] = true;

        if (rr - row <= i)
          cur[rr * MAX_SIZE + i - (rr - row)] = true;
      }

      solve(n, outs, cur, row + 1);
    }
  }

public:
  static std::vector<std::vector<std::string>> solveNQueens(int n)
  {
    // ok, we are going to be representing each row with a bool vector
    std::bitset<MAX_SIZE * MAX_SIZE> board;
    std::vector<std::vector<std::string>> outs;

    solve(n, outs, board, 0);
    return outs;
  }
};

int
main()
{
  return 0;
}
