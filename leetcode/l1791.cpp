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
  static constexpr int findCenter(const std::vector<std::vector<int>>& edges)
  {
    const auto& edgeA = edges[0];
    const auto& edgeB = edges[1];

    if (edgeA[0] == edgeB[0]) {
      return edgeA[0];
    } else if (edgeA[0] == edgeB[1]) {
      return edgeA[0];
    } else {
      return edgeA[1];
    }
  }
};
