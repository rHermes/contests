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
  static int removeDuplicates(std::vector<int>& nums)
  {
    auto [ret, last] = std::ranges::unique(nums);
    nums.erase(ret, last);

    return nums.size();
  }
};

int
main()
{
  return 0;
}
