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
  static constexpr int smallerThan(const std::vector<int>& nums, const int target)
  {
    int smaller = 0;

    int l = 0;
    const int N = nums.size();
    for (int r = 1; r < N; r++) {
      while (l < r && (target <= (nums[r] - nums[l]))) {
        l++;
      }

      smaller += r - l;
    }

    return smaller;
  }

public:
  static constexpr int smallestDistancePair(std::vector<int>& nums, int k)
  {
    // ok, ok, so since it's the smallest distance, we can actually just sort the numbers
    std::ranges::sort(nums);

    int lo = 0;
    int hi = nums.back() - nums.front() + 1;

    while (lo + 1 < hi) {
      const auto mid = std::midpoint(lo, hi);
      const auto smaller = smallerThan(nums, mid);

      if (k <= smaller)
        hi = mid;
      else
        lo = mid;
    }

    return lo;
  }
};
