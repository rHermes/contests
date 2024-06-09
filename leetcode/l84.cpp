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
  static int largestRectangleArea(const std::vector<int>& heights)
  {
    const int N = heights.size();

    // position val
    std::vector<std::pair<int, int>> stack;
    stack.emplace_back(-1, -1);
    int ans = 0;

    for (int i = 0; i < N; i++) {
      const int x = heights[i];

      int prevR = i;
      while (x < stack.back().second) {
        const auto [prevPos, y] = stack.back();
        stack.pop_back();

        prevR = prevPos;

        ans = std::max(ans, y * (i - prevPos));
      }

      if (stack.back().second < x) {
        stack.emplace_back(prevR, x);
      }
    }

    while (!stack.empty()) {
      const auto [prevPos, y] = stack.back();
      stack.pop_back();
      ans = std::max(ans, y * (N - prevPos));
    }

    return ans;
  }
};
