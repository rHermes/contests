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
  static std::vector<int> nextGreaterElements(const std::vector<int>& nums)
  {
    const int N = nums.size();
    std::vector<int> out(N, -1);

    std::vector<int> st;

    for (int i = 0; i < N; i++) {
      while (!st.empty() && nums[st.back()] < nums[i]) {
        out[st.back()] = nums[i];
        st.pop_back();
      }

      st.push_back(i);
    }

    if (st.size() <= 1) {
      return out;
    }

    // ok, now then we are doing the round search.
    for (int i = 0; i < N; i++) {
      while (nums[st.back()] < nums[i]) {
        out[st.back()] = nums[i];
        st.pop_back();

        if (st.size() <= 1) {
          return out;
        }
      }
    }

    return out;
  }
};
