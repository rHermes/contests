#include <algorithm>
#include <iostream>
#include <map>
#include <tuple>
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
  static int jobScheduling(const std::vector<int>& startTime,
                           const std::vector<int>& endTime,
                           const std::vector<int>& profit)
  {

    std::vector<int> indexes(startTime.size());
    for (int i = 0; i < static_cast<int>(indexes.size()); i++)
      indexes[i] = i;

    std::sort(indexes.begin(), indexes.end(), [&](int a, int b) {
      return std::tie(startTime[b], endTime[b]) < std::tie(startTime[a], endTime[a]);
    });

    // This map is a map from: position -> max we can make.
    std::map<int, int> best;
    best.emplace(1000000001, 0);

    for (const auto idx : indexes) {
      // No because of the way we are processing them.
      auto cit = best.lower_bound(endTime[idx]);
      auto kit = best.lower_bound(startTime[idx]);
      const auto score = profit[idx];

      if (kit->second < cit->second + score) {
        best[startTime[idx]] = cit->second + score;
      }
    }

    return best.begin()->second;
  }
};
