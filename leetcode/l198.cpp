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

    int prevPrev = 0;
    int prev = 0;
    int cur = 0;
    for (std::size_t i = 0; i < nums.size(); i++) {
      prevPrev = prev;
      prev = cur;
      cur = std::max(prev, nums[i] + prevPrev);
    }

    return cur;
  }
};

int
main()
{
  return 0;
}
