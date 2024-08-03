#include <iostream>
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
  static std::vector<int> nextGreaterElement(const std::vector<int>& nums1, const std::vector<int>& nums2)
  {
    const int N = nums1.size();
    const int M = nums2.size();

    std::vector<int> st;
    std::unordered_map<int, int> del;

    for (int i = 0; i < M; i++) {
      const int x = nums2[i];
      while (!st.empty() && st.back() < x) {
        del.emplace(st.back(), x);
        st.pop_back();
      }

      st.push_back(x);
    }

    std::vector<int> out(N);
    for (int i = 0; i < N; i++) {
      if (auto it = del.find(nums1[i]); it != del.end())
        out[i] = it->second;
      else
        out[i] = -1;
    }

    return out;
  }
};
