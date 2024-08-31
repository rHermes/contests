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
  static constexpr int jump(const std::vector<int>& nums)
  {
    int l = 0;
    int r = 0;
    int jumps = 0;
    const int N = nums.size();
    while (r < N - 1) {
      int farthest = l + nums[l];
      for (int idx = l + 1; idx <= r; idx++)
        farthest = std::max(farthest, idx + nums[idx]);

      l = r + 1;
      r = farthest;
      jumps++;
    }

    return jumps;
  }
};
