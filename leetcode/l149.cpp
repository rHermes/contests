#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

struct pair_hash
{
  size_t operator()(const std::pair<int, int>& p) const { return ((size_t)p.first << 32) | p.second; }
};

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static int maxPoints(const std::vector<std::vector<int>>& points)
  {
    const auto N = points.size();

    if (N <= 2)
      return N;

    int ans = 2;

    // We are using manual fractions, as
    std::unordered_map<std::pair<int, int>, int, pair_hash> slopes;

    // ok, so we are now going to check.
    for (std::size_t i = 0; i < N - 1; i++) {
      slopes.clear();

      const auto x1 = points[i][0];
      const auto y1 = points[i][1];

      int vert = 1;
      for (std::size_t j = i + 1; j < N; j++) {
        const auto x2 = points[j][0];
        const auto y2 = points[j][1];

        if (x1 == x2) {
          vert++;
          continue;
        }

        // Ok, let's reduce it to it's signature function.
        // we are flipping on the x axis here, as we want them all
        // to share the same sign.
        auto deltaY = (x2 < x1) ? (y1 - y2) : (y2 - y1);
        auto deltaX = (x2 < x1) ? (x1 - x2) : (x2 - x1);
        const auto com1 = std::gcd(deltaY, deltaX);
        deltaY /= com1;
        deltaX /= com1;

        auto ik = ++slopes[{ deltaY, deltaX }];
        ans = std::max(ans, ik + 1);
      }

      ans = std::max(ans, vert);
    }

    return ans;
  }
};
