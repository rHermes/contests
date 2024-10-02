#include <algorithm>
#include <iostream>
#include <memory>
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
  static std::vector<int> arrayRankTransform(std::vector<int>& arr)
  {
    using T = std::pair<int, int>;

    const int N = arr.size();
    if (N == 0)
      return {};

    auto tmpRaw = std::make_unique_for_overwrite<T[]>(N);
    std::span<T> tmp(tmpRaw.get(), N);

    for (int i = 0; i < N; i++) {
      tmpRaw[i] = { arr[i], i };
    }

    std::ranges::sort(tmp, [](const auto& a, const auto& b) { return a.first < b.first; });

    int rank = 1;
    for (int i = 0; i < N - 1; i++) {
      const auto& [curVal, curIdx] = tmp[i];
      const auto& [nextVal, nextIdx] = tmp[i + 1];

      if (curVal != nextVal) {
        arr[curIdx] = rank++;
      } else {
        arr[curIdx] = rank;
      }
    }

    arr[tmp[N - 1].second] = rank;

    return arr;
  }
};
