#include <iostream>
#include <limits>
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
  static int findMinDifference(const std::vector<std::string>& timePoints)
  {
    constexpr int MAXN = 24 * 60;
    std::vector<unsigned char> seen(MAXN);

    constexpr auto convertIt = [](const std::string& fmt) {
      return 600 * (fmt[0] - '0') + 60 * (fmt[1] - '0') + 10 * (fmt[3] - '0') + (fmt[4] - '0');
    };

    int minX = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::lowest();

    for (const auto& ts : timePoints) {
      const int cur = convertIt(ts);
      if (seen[cur])
        return 0;

      seen[cur] = true;
      minX = std::min(minX, cur);
      maxX = std::max(maxX, cur);
    }

    int minDiff = minX + MAXN - maxX;

    int prev = minX;
    for (int cur = minX + 1; cur <= maxX; cur++) {
      if (!seen[cur])
        continue;

      minDiff = std::min(minDiff, cur - prev);
      prev = cur;
    }

    return minDiff;
  }
};
