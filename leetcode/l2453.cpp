#include <iostream>
#include <limits>
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
  static int destroyTargets(const std::vector<int>& nums, int space)
  {
    std::unordered_map<int, int> dp;

    int maxi = 0;
    for (const auto n : nums) {
      maxi = std::max(maxi, ++dp[n % space]);
    }

    int ans = std::numeric_limits<int>::max();
    for (const auto n : nums) {
      if (dp[n % space] == maxi)
        ans = std::min(ans, n);
    }
    return ans;
  }
};

int
main()
{
  return 0;
}
