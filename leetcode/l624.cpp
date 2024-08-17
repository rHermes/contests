#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
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
  static constexpr int maxDistance(const std::vector<std::vector<int>>& arrays)
  {
    // We just find the min and max?
    // we are never interested in anything but the first and last digits.
    const int M = arrays.size();
    std::vector<int> idxs(M);
    std::iota(idxs.begin(), idxs.end(), 0);

    std::array<int, 2> smallest{};
    std::array<int, 2> biggest{};

    std::ranges::partial_sort_copy(
      idxs, smallest, [&](const int i, const int j) { return arrays[i].front() < arrays[j].front(); });

    std::ranges::partial_sort_copy(
      idxs, biggest, [&](const int i, const int j) { return arrays[j].back() < arrays[i].back(); });

    if (smallest[0] != biggest[0]) {
      return arrays[biggest[0]].back() - arrays[smallest[0]].front();
    } else {
      const int optOne = arrays[biggest[0]].back() - arrays[smallest[1]].front();
      const int optTwo = arrays[biggest[1]].back() - arrays[smallest[0]].front();
      return std::max(optOne, optTwo);
    }
  }
};
