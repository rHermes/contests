#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
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
  static constexpr int minDifference(const std::vector<int>& nums)
  {
    const int N = nums.size();
    if (N <= 4) {
      return 0;
    }
    std::array<int, 5> mins{};
    std::ranges::copy(nums.begin(), nums.begin() + 5, mins.begin());
    std::array<int, 5> maxs = mins;

    std::ranges::make_heap(mins);
    std::ranges::make_heap(maxs, std::ranges::greater{});

    for (int i = 5; i < N; i++) {
      const auto x = nums[i];
      if (x < mins[0]) {
        std::ranges::pop_heap(mins);
        mins[4] = x;
        std::ranges::push_heap(mins);
      }

      if (maxs[0] < x) {
        std::ranges::pop_heap(maxs, std::ranges::greater{});
        maxs[4] = x;
        std::ranges::push_heap(maxs, std::ranges::greater{});
      }
    }
    std::ranges::sort_heap(mins);
    std::ranges::sort_heap(maxs, std::ranges::greater{});

    int ans = std::numeric_limits<int>::max();
    for (int i = 0; i < 4; i++) {
      const auto a = mins[i];
      const auto b = maxs[3 - i];
      if (a <= b)
        ans = std::min(ans, b - a);
    }

    return ans;
  }
};
