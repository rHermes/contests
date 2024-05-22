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
  static long long maxArrayValue(const std::vector<int>& nums)
  {
    const int N = nums.size();

    long long ans = 0;
    long long prev = 0;
    for (int i = N - 1; 0 <= i; i--) {
      if (nums[i] <= prev) {
        prev += nums[i];
      } else {
        prev = nums[i];
      }

      ans = std::max(prev, ans);
    }

    return ans;
  }
};

int
main()
{
  return 0;
}
