#include <numeric>

class Solution
{
public:
  static constexpr int nthUglyNumber(int n, int a, int b, int c)
  {
    const auto ab = std::lcm<long long, long long>(a, b);
    const auto ac = std::lcm<long long, long long>(a, c);
    const auto bc = std::lcm<long long, long long>(b, c);
    const auto abc = std::lcm<long long, long long>(ab, c);

    long long lo = 1;
    long long hi = 2000000000 + 1;

    while (lo + 1 < hi) {
      const auto mid1 = std::midpoint(lo, hi);
      const auto mid = mid1 - 1;

      // Let's see how many divide a
      auto aD = mid / a;
      auto bD = mid / b;
      auto cD = mid / c;

      // let's see how many are divisible by a*b
      auto abD = mid / ab;
      auto acD = mid / ac;
      auto bcD = mid / bc;

      auto abcD = mid / abc;

      // We are using the inclusion-exclusion principle here
      auto nth = aD + bD + cD - abD - acD - bcD + abcD;

      if (nth < n) {
        lo = mid1;
      } else {
        hi = mid1;
      }
    };
    return lo;
  }
};
