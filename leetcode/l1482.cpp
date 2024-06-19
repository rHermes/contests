#include <algorithm>
#include <iostream>
#include <numeric>
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
  static constexpr int minDays(const std::vector<int>& bloomDay, int m, int k)
  {
    const int N = bloomDay.size();

    int ans = -1;
    int lo = 0;
    int hi = *std::ranges::max_element(bloomDay) + 1;

    while (lo <= hi) {
      const int mid = std::midpoint(lo, hi);

      int count = 0;
      int taken = 0;
      for (int r = 0; r < N; r++) {
        if (bloomDay[r] <= mid) {
          count++;
        } else {
          count = 0;
        }

        if (k <= count) {
          count = 0;
          taken++;
        }
      }

      if (m <= taken) {
        ans = mid;
        hi = mid - 1;
      } else {
        lo = mid + 1;
      }
    }

    return ans;
  }
};
