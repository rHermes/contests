#include <cmath>
#include <cstdint>

class Solution
{
public:
  static bool judgeSquareSum(const int c)
  {
    std::int64_t left = 0;
    std::int64_t right = std::sqrt(c) + 1;

    while (left <= right) {
      const auto res = left * left + right * right;
      if (res == c) {
        return true;
      }

      if (res < c) {
        left++;
      } else {
        right--;
      }
    }

    return false;
  }
};
