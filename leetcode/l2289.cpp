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
  static constexpr int totalSteps(const std::vector<int>& nums)
  {
    const int N = nums.size();
    std::vector<std::pair<int, int>> st;

    int ans = 0;
    for (int i = 0; i < N; i++) {
      int cur = 0;
      while (!st.empty() && nums[st.back().first] <= nums[i]) {
        cur = std::max(cur, st.back().second);
        st.pop_back();
      }

      if (!st.empty()) {
        ans = std::max(ans, cur + 1);
        st.emplace_back(i, cur + 1);
      } else {
        st.emplace_back(i, 0);
      }
    }

    return ans;
  }
};
