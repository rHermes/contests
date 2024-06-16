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
  static int partitionDisjoint(const std::vector<int>& nums)
  {
    const int N = nums.size();
    std::vector<int> temps(N);
    temps[N - 1] = nums[N - 1];
    for (int i = N - 2; 0 <= i; i--) {
      temps[i] = std::min(nums[i], temps[i + 1]);
    }

    int maxLeft = nums[0];
    for (int i = 1; i < N; i++) {
      if (maxLeft <= temps[i])
        return i;

      maxLeft = std::max(nums[i], maxLeft);
    }

    return -1;
  }
};
