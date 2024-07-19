#include <algorithm>
#include <iostream>
#include <limits>
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
  static std::vector<int> luckyNumbers(const std::vector<std::vector<int>>& matrix)
  {
    const int M = matrix.size();
    const int N = matrix[0].size();

    std::vector<int> cols(N, std::numeric_limits<int>::lowest());
    std::vector<int> rows(M, std::numeric_limits<int>::max());

    for (int row = 0; row < M; row++) {
      for (int col = 0; col < N; col++) {
        const auto val = matrix[row][col];
        cols[col] = std::max(cols[col], val);
        rows[row] = std::min(rows[row], val);
      }
    }

    std::ranges::sort(cols);
    std::ranges::sort(rows);

    std::vector<int> out;
    out.reserve(M + N);
    std::ranges::set_intersection(cols, rows, std::back_inserter(out));

    return out;
  }
};
