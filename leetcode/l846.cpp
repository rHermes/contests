#include <algorithm>
#include <deque>
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
  static bool isNStraightHand(std::vector<int>& hand, int groupSize)
  {
    if (groupSize == 1)
      return true;

    if (hand.size() % groupSize != 0)
      return false;

    // front, size
    std::deque<std::pair<int, int>> groups;
    std::ranges::sort(hand);

    for (const auto x : hand) {
      if (groups.empty()) {
        groups.emplace_front(x, 1);
        continue;
      }

      if (x == groups.front().first) {
        groups.emplace_back(x, 1);
      } else if (x == groups.front().first + 1) {
        const auto sz = groups.front().second + 1;
        groups.pop_front();
        if (sz != groupSize)
          groups.emplace_back(x, sz);
      } else {
        return false;
      }
    }

    return groups.empty();
  }
};
