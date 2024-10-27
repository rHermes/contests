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
  static int countSquares(std::vector<std::vector<int>>& matrix)
  {
    // This is a cool task, let's see here
    const int ROWS = matrix.size();
    const int COLS = matrix[0].size();

    int ans = 0;
    for (int i = 0; i < ROWS; i++) {
      ans += matrix[i][0];
    }
    for (int j = 1; j < COLS; j++) {
      ans += matrix[0][j];
    }

    for (int i = 1; i < ROWS; i++) {
      for (int j = 1; j < COLS; j++) {
        if (matrix[i][j] == 0)
          continue;

        matrix[i][j] = std::min({ matrix[i - 1][j], matrix[i][j - 1], matrix[i - 1][j - 1] }) + 1;

        ans += matrix[i][j];
      }
    }

    return ans;
  }
};
