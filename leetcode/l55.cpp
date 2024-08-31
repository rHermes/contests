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
  static constexpr bool canJump(const std::vector<int>& nums)
  {
    int space = 0;
    for (const auto gs : nums) {
      if (space < 0)
        return false;

      space = std::max(space, gs) - 1;
    }
    return true;
  }
};
