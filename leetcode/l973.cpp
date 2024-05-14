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
  static std::vector<std::vector<int>> kClosest(const std::vector<std::vector<int>>& points, int k)
  {

    std::vector<std::tuple<int, int, int>> K(k, std::tuple{ std::numeric_limits<int>::max(), 0, 0 });

    for (const auto& pt : points) {
      const auto x = pt[0];
      const auto y = pt[1];

      const auto dst = x * x + y * y;

      if (dst < std::get<0>(K[0])) {
        std::ranges::pop_heap(K);
        K.back() = { dst, x, y };
        std::ranges::push_heap(K);
      }
    }

    std::vector<std::vector<int>> out(k);
    for (int i = 0; i < k; i++) {
      const auto [_, x, y] = K[i];
      out[i] = { x, y };
    }
    return out;
  }
};

int
main()
{
  return 0;
}
