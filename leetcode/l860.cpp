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
  static constexpr bool lemonadeChange(const std::vector<int>& bills)
  {
    int fives = 0;
    int tens = 0;

    for (const auto x : bills) {
      if (x == 5) {
        fives++;
      } else if (x == 10) {
        if (--fives < 0)
          return false;

        tens++;
      } else {
        if (--fives < 0)
          return false;

        if (0 < tens) {
          tens--;
        } else if (2 <= fives) {
          fives -= 2;
        } else {
          return false;
        }
      }
    }

    return true;
  }
};
