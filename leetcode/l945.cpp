#include <algorithm>
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
  static int minIncrementForUnique(std::vector<int>& nums)
  {
    std::ranges::sort(nums);
    int ans = 0;
    for (std::size_t i = 1; i < nums.size(); i++) {
      if (nums[i] <= nums[i - 1]) {
        ans += (nums[i - 1] - nums[i]) + 1;
        nums[i] = nums[i - 1] + 1;
      }
    }

    return ans;
  }
};
