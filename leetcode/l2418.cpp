#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
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
  static std::vector<std::string> sortPeople(std::vector<std::string>& names, const std::vector<int>& heights)
  {
    const int N = names.size();

    std::vector<int> idx(N);
    std::iota(idx.begin(), idx.end(), 0);

    std::ranges::sort(idx, [&](const int i, const int j) { return heights[j] < heights[i]; });

    for (int i = 0; i < N; i++) {
      if (idx[i] == -1)
        continue;

      int j = i;
      while (i != idx[j]) {
        std::swap(names[j], names[idx[j]]);
        j = std::exchange(idx[j], -1);
      }
      idx[j] = -1;
    }

    return std::move(names);
  }
};
