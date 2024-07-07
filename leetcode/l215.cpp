#include <algorithm>
#include <array>
#include <iostream>
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
  static constexpr int findKthLargest(std::vector<int>& nums, int k)
  {
    // Showing the two ways to do this. One based on counting sort
    // and the other based on the standard library.
    if constexpr (true) {
      auto spot = nums.begin() + k - 1;
      std::ranges::nth_element(nums, spot, std::ranges::greater{});
      return *spot;
    } else {
      constexpr int MAXN = 10000;
      std::array<int, 2 * MAXN + 1> cnt{};
      for (const auto x : nums) {
        cnt[MAXN + x]++;
      }

      int rest = k;
      for (int i = 2 * MAXN; 0 <= i; i--) {
        rest -= cnt[i];
        if (rest <= 0) {
          return i - MAXN;
        }
      }

      return -1;
    }
  }
};
