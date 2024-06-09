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
  static constexpr std::vector<double> sampleStats(const std::vector<int>& count)
  {
    int mmin = 256;
    int mmax = 0;
    long sum = 0;
    int cnt = 0;
    int mmost = 0;

    for (int i = 0; i < 256; i++) {
      if (count[i] == 0)
        continue;

      if (mmin == 256)
        mmin = i;

      mmax = i;

      sum += static_cast<long>(i) * count[i];
      cnt += count[i];

      if (count[mmost] < count[i])
        mmost = i;
    }

    const double dmin = mmin;
    const double dmax = mmax;
    const double dmost = mmost;
    const double davg = static_cast<double>(sum) / cnt;

    int target = (cnt - 1) / 2;

    for (int i = 0; i < 256; i++) {
      const int x = count[i];
      if (x <= target) {
        target -= x;
        continue;
      }

      if (cnt % 2 != 0) {
        return { dmin, dmax, davg, static_cast<double>(i), dmost };
      } else {
        if (target < x - 1) {
          return { dmin, dmax, davg, static_cast<double>(i), dmost };
        }

        for (int j = i + 1; j < 256; j++) {
          if (0 < count[j]) {
            return { dmin, dmax, davg, std::midpoint<double>(i, j), dmost };
          }
        }
      }
    }

    throw std::runtime_error("We should never reach this");
  }
};
