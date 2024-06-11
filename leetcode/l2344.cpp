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
  static int minOperations(std::vector<int>& nums, const std::vector<int>& numsDivide)
  {
    const int target = std::reduce(numsDivide.begin(), numsDivide.end(), numsDivide.front(), std::gcd<int, int>);
    std::ranges::sort(nums);
    for (std::size_t i = 0; i < nums.size(); i++) {
      if (target < nums[i])
        break;

      if (target % nums[i] == 0)
        return i;
    }
    return -1;
  }
};
