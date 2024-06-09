#include <algorithm>
#include <iostream>
#include <limits>
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
  constexpr static long long maximumValueSum(const std::vector<int>& nums,
                                             const int k,
                                             const std::vector<std::vector<int>>& edges)
  {
    std::ignore = edges;
    long long result = 0;
    long long alt_result = -std::numeric_limits<long long>::max();

    for (const auto n : nums) {
      const auto tmp = result;
      const auto alt_n = n ^ k;

      result = std::max(result + n, alt_result + alt_n);
      alt_result = std::max(alt_result + n, tmp + alt_n);
    }

    return result;
  }
};
