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
  static constexpr bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target)
  {
    std::size_t rows = matrix.size();
    std::size_t cols = matrix[0].size();

    std::size_t row = 0;
    std::size_t col = cols;
    while (0 < col && row < rows) {
      auto ans = matrix[row][col - 1];
      if (ans == target) {
        return true;
      } else if (target < ans) {
        col--;
      } else {
        row++;
      }
    }
    return false;
  }
};
