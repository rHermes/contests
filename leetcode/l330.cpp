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
  static constexpr int minPatches(const std::vector<int>& nums, int n)
  {
    std::int64_t cover = 0;
    std::int64_t ans = 0;

    int i = 0;
    const int N = nums.size();
    while (cover < n && i < N) {
      const int x = nums[i];
      if (cover + 1 < x) {
        ans++;
        cover += cover + 1;
      } else {
        cover += x;
        i++;
      }
    }

    while (cover + 1 < n) {
      ans++;
      cover += cover + 1;
    }

    return ans;
  }
};
