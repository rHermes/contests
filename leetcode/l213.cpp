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
  static int rob(const std::vector<int>& nums)
  {
    const auto helper = [&](int start, int end) {
      int prevPrev = 0;
      int prev = 0;
      int cur = start;
      for (int i = 1; i < end; i++) {
        prevPrev = prev;
        prev = cur;
        cur = std::max(prev, nums[i] + prevPrev);
      }
      return cur;
    };

    return std::max(helper(0, nums.size()), helper(nums[0], nums.size() - 1));
  }
};

int
main()
{
  return 0;
}
