#include <algorithm>
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
  static std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k)
  {
    // The reason we are comparing it like this, rather than partial_sort
    // is that this c++ implementation for partial_sort is slower than
    // the total sort.
    std::ranges::sort(
      points, [](const auto& a, const auto& b) { return (a[0] * a[0] + a[1] * a[1]) < (b[0] * b[0] + b[1] * b[1]); });

    // We resize to just the points we want.
    points.resize(k);

    return std::move(points);
  }
};

int
main()
{
  return 0;
}
