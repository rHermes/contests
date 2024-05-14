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
  static int minCapability(const std::vector<int>& nums, const int k)
  {
    const int N = nums.size();

    const auto check = [&](const int cap) {
      int count = 0;

      for (int i = 0; i < N; i++) {
        if (nums[i] <= cap) {
          count++;
          i++;
          if (k == count)
            return true;
        }
      }

      return false;
    };

    auto [lo, hi] = std::ranges::minmax(nums);

    while (lo < hi) {
      const auto mid = std::midpoint(lo, hi);

      if (check(mid)) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }

    return lo;
  }
};

int
main()
{
  return 0;
}
