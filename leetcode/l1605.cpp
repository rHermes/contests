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
  static std::vector<std::vector<int>> restoreMatrix(std::vector<int>& rowSum, std::vector<int>& colSum)
  {
    const int ROWS = rowSum.size();
    const int COLS = colSum.size();

    std::vector<std::vector<int>> out(ROWS, std::vector<int>(COLS, 0));

    int row = 0;
    int col = 0;
    while (true) {
      if (rowSum[row] < colSum[col]) {
        out[row][col] = rowSum[row];
        colSum[col] -= rowSum[row];
        if (++row == ROWS)
          break;
      } else {
        out[row][col] = colSum[col];
        rowSum[row] -= colSum[col];
        if (++col == COLS)
          break;
      }
    }

    return out;
  }
};
;
