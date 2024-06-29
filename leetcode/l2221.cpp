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
  int triangularSum(std::vector<int>& nums)
  {
    int N = nums.size();
    while (1 < N) {
      for (int i = 0; i < N - 1; i++) {
        nums[i] = (nums[i] + nums[i + 1]) % 10;
      }
      N--;
    }

    return nums[0];
  }
};
