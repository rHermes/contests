#include <numeric>

class Solution
{
public:
  static constexpr int mySqrt(int x)
  {
    if (x < 2)
      return x;

    int lo = 1;
    int hi = x / 2 + 1;
    int ans = lo;

    while (lo < hi) {
      int mid = std::midpoint(lo, hi);

      if (mid <= x / mid) {
        ans = mid;
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    return ans;
  }
};

int
main()
{
  return 0;
}
