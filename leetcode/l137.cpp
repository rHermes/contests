#include <cstdint>
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
  static constexpr int singleNumber(const std::vector<int>& nums)
  {
    std::uint32_t seen_once = 0;
    std::uint32_t seen_twice = 0;

    for (const auto x : nums) {
      std::uint32_t cur = x;
      seen_once = (~seen_twice) & (seen_once ^ cur);
      seen_twice = (~seen_once) & (seen_twice ^ cur);
    }

    return seen_once;
  }
};
