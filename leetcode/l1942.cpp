#include <algorithm>
#include <iostream>
#include <numeric>
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
  static constexpr int smallestChair(const std::vector<std::vector<int>>& times, const int targetFriend)
  {
    const int N = times.size();

    std::vector<int> indices(N);
    std::iota(indices.begin(), indices.end(), 0);
    std::ranges::sort(indices, [&](const auto a, const auto b) { return times[a][0] < times[b][0]; });

    std::priority_queue<int, std::vector<int>, std::ranges::greater> spots;

    constexpr auto sortPair = [](const auto& a, const auto& b) { return b.first < a.first; };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(sortPair)> leaveQ;

    int nextSpot = 0;

    for (const auto idx : indices) {
      const auto arrival = times[idx][0];
      const auto departure = times[idx][1];

      while (!leaveQ.empty() && leaveQ.top().first <= arrival) {
        spots.emplace(leaveQ.top().second);
        leaveQ.pop();
      }

      auto chair = spots.empty() ? nextSpot++ : spots.top();
      if (!spots.empty()) {
        spots.pop();
      }

      if (idx == targetFriend) {
        return chair;
      }

      leaveQ.emplace(departure, chair);
    }

    return -1;
  }
};
