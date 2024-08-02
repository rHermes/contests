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
  static constexpr int minSwaps(const std::vector<int>& nums)
  {
    const int N = nums.size();
    const int SN = std::reduce(nums.begin(), nums.end(), 0);
    if (SN == N)
      return 0;

    int rs = SN;
    for (int i = 0; i < SN; i++) {
      rs -= nums[i];
    }

    int ans = rs;
    for (int i = SN; i < N + SN; i++) {
      rs -= nums[i % N] - nums[i - SN];

      ans = std::min(ans, rs);
    }
    return ans;
  }
};
