#include <algorithm>
#include <cstdint>
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
  static bool asteroidsDestroyed(int mass, std::vector<int>& asteroids)
  {
    std::int64_t cur = mass;
    std::ranges::sort(asteroids);
    for (const auto& x : asteroids) {
      if (x <= cur)
        cur += x;
      else
        return false;
    }
    return true;
  }
};
