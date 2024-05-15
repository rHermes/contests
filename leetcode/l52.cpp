#include <bitset>
#include <iostream>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  static constexpr int MAX_SIZE = 9;
  static int solve(const int n, std::bitset<MAX_SIZE * MAX_SIZE> board, const int row)
  {
    if (row == n) {
      return 1;
    }

    auto filledPrev = board;
    for (int i = 0; i < n; i++)
      filledPrev[row * MAX_SIZE + i] = true;

    int ans = 0;
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

      ans += solve(n, cur, row + 1);
    }

    return ans;
  }

public:
  static int totalNQueens(int n)
  {
    // ok, we are going to be representing each row with a bool vector
    std::bitset<MAX_SIZE * MAX_SIZE> board;
    return solve(n, board, 0);
  }
};

int
main()
{
  return 0;
}
