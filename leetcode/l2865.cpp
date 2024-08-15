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
  static constexpr long long maximumSumOfHeights(const std::vector<int>& heights)
  {
    const int N = heights.size();

    std::vector<long long> maxLeft(N);
    // pos, height.
    std::vector<std::pair<int, int>> stack;
    stack.emplace_back(-1, 0);

    long long curSum = 0;

    for (int i = 0; i < N; i++) {

      const auto x = heights[i];

      while (x <= stack.back().second) {
        // How many bricks are we losing here? Well, it's until the next position.
        const auto [remPos, remHeight] = stack.back();
        stack.pop_back();
        const auto& [prevPos, prevHeight] = stack.back();

        const auto areaRemoved = (remPos - prevPos) * static_cast<long long>(remHeight - x);
        curSum -= areaRemoved;
      }

      curSum += x;
      maxLeft[i] = curSum;

      stack.emplace_back(i, x);
    }

    long long ans = curSum;

    stack.clear();
    stack.emplace_back(N, 0);
    curSum = 0;

    for (int i = N - 1; 0 <= i; i--) {
      const auto x = heights[i];

      while (x <= stack.back().second) {
        const auto [remPos, remHeight] = stack.back();
        stack.pop_back();
        const auto& [prevPos, prevHeight] = stack.back();

        const auto areaRemoved = (prevPos - remPos) * static_cast<long long>(remHeight - x);
        curSum -= areaRemoved;
      }

      ans = std::max(ans, curSum + maxLeft[i]);

      curSum += x;
      stack.emplace_back(i, x);
    }

    ans = std::max(ans, curSum);

    return ans;
  }
};
