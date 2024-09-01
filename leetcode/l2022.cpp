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
  std::vector<std::vector<int>> construct2DArray(const std::vector<int>& original, const int M, const int N)
  {
    if (M * N != static_cast<int>(original.size())) {
      return {};
    }
    std::vector<std::vector<int>> out(M, std::vector<int>(N));
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        out[i][j] = original[i * N + j];
      }
    }

    return out;
  }
};
