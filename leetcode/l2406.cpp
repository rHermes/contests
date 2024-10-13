#include <algorithm>
#include <iostream>
#include <queue>
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
  static int minGroups(std::vector<std::vector<int>>& intervals)
  {
    std::ranges::sort(intervals);
    std::priority_queue<int, std::vector<int>, std::ranges::greater> Q;

    int ans = 1;

    for (const auto& inter : intervals) {
      const auto from = inter[0];
      const auto to = inter[1];

      while (!Q.empty() && Q.top() < from) {
        Q.pop();
      }
      Q.push(to);
      ans = std::max(static_cast<int>(Q.size()), ans);
    }

    return ans;
  }
};
