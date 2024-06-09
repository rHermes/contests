#include <cstdint>
#include <iostream>
#include <unordered_map>
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
  static bool checkSubarraySum(const std::vector<int>& nums, int k)
  {
    const int N = nums.size();
    std::int32_t accum = 0;

    std::unordered_map<std::int32_t, int> seen;
    seen.reserve(100);
    seen[0] = -1;
    for (int r = 0; r < N; r++) {
      accum = (accum + nums[r]) % k;

      auto [it, inserted] = seen.emplace(accum, r);
      if (!inserted) {
        if (1 < r - it->second)
          return true;
      }
    }

    return false;
  }
};
