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
  static constexpr bool find132pattern(const std::vector<int>& nums)
  {
    const int N = nums.size();
    if (N < 3)
      return false;

    // We keep a stack of the current intervals.
    std::vector<std::pair<int, int>> st;
    for (const auto num : nums) {
      if (st.empty() || num < st.back().first) {
        // We have a new minimum.
        st.emplace_back(num, num);
      } else {
        const auto mini = st.back().first;
        // We can always grow the later stacks, and they will always
        // be bigger than the current one. So if we are expanding in the
        // upwards direction, we are always going to be popping off from
        // the back
        while (!st.empty() && st.back().second < num) {
          st.pop_back();
        }

        if (!st.empty() && st.back().first < num && num < st.back().second)
          return true;

        // This is the new range.
        st.emplace_back(mini, num);
      }
    }

    return false;
  }
};
