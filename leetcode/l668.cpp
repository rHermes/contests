#include <algorithm>
#include <numeric>
#include <utility>

class Solution
{
public:
  constexpr static int findKthNumber(int ROWS, int COLS, const int K)
  {
    if (COLS < ROWS)
      std::swap(COLS, ROWS);

    int lo = 0;
    int hi = K;

    while (lo + 1 < hi) {
      const int mid = std::midpoint(lo, hi);

      int belowOrEq = 0;
      for (int row = 1; row <= ROWS; row++) {
        belowOrEq += std::min(mid / row, COLS);
      }

      if (belowOrEq < K) {
        lo = mid;
      } else {
        hi = mid;
      }
    }

    return hi;
  }
};
