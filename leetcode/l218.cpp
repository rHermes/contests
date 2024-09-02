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
  static std::vector<std::vector<int>> getSkyline(const std::vector<std::vector<int>>& buildings)
  {
    // ok, in the end, we use a heap and track the tops that way.
    // It's a bit messy, but it works out.
    std::vector<std::vector<int>> out;

    const auto heightChange = [&](const int x, const int h) {
      // ok, if the height change happened,
      const auto prevX = out.back()[0];
      const auto prevH = out.back()[1];

      if (x == prevX) {
        out.back()[1] = std::max(prevH, h);
      } else {
        out.push_back({ x, h });
      }
    };

    // Height, right edge.
    std::priority_queue<std::pair<int, int>> tallest;

    const auto processOne = [&]() {
      const auto [prevHight, prevRight] = tallest.top();
      tallest.pop();

      // Remove all houses I covered, which we couldn't filter out before insertion.
      while (!tallest.empty() && tallest.top().second <= prevRight) {
        tallest.pop();
      }

      heightChange(prevRight, tallest.empty() ? 0 : tallest.top().first);
    };

    const auto processUntil = [&](const int x) {
      while (!tallest.empty() && tallest.top().second < x) {
        processOne();
      }
    };

    // To avoid empty checks for out, we insert the first building, as it's always going
    // to be the first bump.
    out.push_back({ buildings[0][0], buildings[0][2] });
    tallest.emplace(buildings[0][2], buildings[0][1]);

    const int N = buildings.size();
    for (int i = 1; i < N; i++) {
      const auto bl = buildings[i][0];
      const auto br = buildings[i][1];
      const auto bh = buildings[i][2];

      // Catch up to the left corner of the building, as we are done
      // with all before it.
      processUntil(bl);

      if (tallest.empty()) {
        tallest.emplace(bh, br);
        heightChange(bl, tallest.top().first);
      } else if (tallest.top().first < bh) {
        tallest.emplace(bh, br);
        heightChange(bl, bh);
      } else if (tallest.top().second < br) {
        tallest.emplace(bh, br);
      }
    }

    // Now we just process the remaining houses and we are done.
    while (!tallest.empty()) {
      processOne();
    }

    return out;
  }
};
