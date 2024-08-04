#include <algorithm>
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
  static constexpr int carFleet(int target, const std::vector<int>& position, const std::vector<int>& speed)
  {
    const int N = position.size();

    std::vector<int> idxes(N);
    std::iota(idxes.begin(), idxes.end(), 0);

    // The position is guaranteed to be unique, so we can just sort on less.
    std::ranges::sort(idxes, [&](const int i, const int j) { return position[i] < position[j]; });

    std::vector<double> st;
    for (const auto idx : idxes) {
      const auto finishTime = static_cast<double>(target - position[idx]) / speed[idx];

      while (!st.empty() && st.back() <= finishTime) {
        st.pop_back();
      }

      st.push_back(finishTime);
    }

    return st.size();
  }
};
