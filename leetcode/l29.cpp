#include <cmath>
#include <limits>

class Solution
{
public:
  static constexpr int divide(const int dividend, const int divisor)
  {
    // Bitshifts are sort of cheating, but ok, we will live with it for now.
    if (dividend == divisor) {
      return 1;
    }

    bool isPositive = (dividend < 0 == divisor < 0);
    unsigned int a = std::abs(dividend);
    unsigned int b = std::abs(divisor);

    unsigned int ans = 0;
    while (b <= a) {
      short q = 0;
      while ((b << (q + 1)) < a) {
        q++;
      }

      ans += (1 << q);
      a = a - (b << q);
    }

    if ((static_cast<unsigned int>(std::numeric_limits<int>::max()) < ans) && isPositive) {
      return std::numeric_limits<int>::max();
    }
    return isPositive ? ans : -ans;
  }
};
