#include <functional>
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
  static constexpr bool xorGame(const std::vector<int>& nums)
  {
    const int ans = std::reduce(nums.begin(), nums.end(), 0, std::bit_xor<>{});
    return (ans == 0 || nums.size() % 2 == 0);
  }
};
