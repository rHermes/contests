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
  static int maxWidthRamp(const std::vector<int>& nums)
  {
    const int N = nums.size();
    std::vector<std::pair<int, int>> st;

    // We create a decreasing ladder on the first pass.
    st.emplace_back(nums[0], 0);
    for (int i = 1; i < N; i++) {
      const auto x = nums[i];
      if (x < st.back().first)
        st.emplace_back(x, i);
    }

    int ans = 0;
    for (int i = N - 1; 0 < i; i--) {
      const auto x = nums[i];

      while (!st.empty() && st.back().first <= x) {
        ans = std::max(ans, i - st.back().second);
        st.pop_back();
      }

      if (st.empty())
        break;
    }

    return ans;
  }
};
