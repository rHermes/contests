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
  static constexpr int maxValueAfterReverse(const std::vector<int>& nums)
  {
    const int N = nums.size();
    int ans = 0;

    int maxi = std::numeric_limits<int>::lowest();
    int mini = std::numeric_limits<int>::max();
    int edge = 0;

    for (int i = 0; i < N - 1; i++) {
      const int a = nums[i];
      const int b = nums[i + 1];
      const auto [c, d] = std::minmax(a, b);

      // Update the best place to switch
      maxi = std::max(c, maxi);
      mini = std::min(d, mini);

      // Update our answer
      ans += d - c;

      // Update the edge conditions
      const int tmp1 = -(d - c) + std::abs(nums[0] - b);
      const int tmp2 = -(d - c) + std::abs(nums.back() - a);
      edge = std::max(edge, std::max(tmp1, tmp2));
    }

    return ans + std::max(edge, (maxi - mini) * 2);
  }
};
