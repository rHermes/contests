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
  static int maxSubArray(const std::vector<int>& nums)
  {
    // There is a two pointer solution here I think
    int ans = nums[0];

    int cur = 0;
    int l = 0;
    for (int r = 0; r < static_cast<int>(nums.size()); r++) {
      cur += nums[r];
      ans = std::max(ans, cur);
      while (l <= r && cur < 0) {
        cur -= nums[l];
        l++;
      }
    }

    return ans;
  }
};
