#include <algorithm>
#include <iostream>
#include <string>
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
  static std::vector<std::string> reorderLogFiles(std::vector<std::string> logs)
  {
    auto vi = std::ranges::stable_partition(logs, [](const std::string& log) {
      auto firstSpot = log.find(' ');
      return log.find_first_not_of("0123456789 ", firstSpot + 1) != log.npos;
    });

    std::ranges::sort(logs.begin(), std::ranges::begin(vi), [](const std::string& a, const std::string& b) {
      auto firstSpotA = a.find(' ');
      auto firstSpotB = b.find(' ');

      const auto lineBeginA = a.begin() + firstSpotA + 1;
      const auto lineBeginB = b.begin() + firstSpotB + 1;

      auto hey = std::lexicographical_compare_three_way(
        lineBeginA, a.end(), lineBeginB, b.end(), [](const char ac, const char bc) {
          if (ac != bc) {
            if (ac == ' ')
              return std::strong_ordering::less;
            if (bc == ' ')
              return std::strong_ordering::greater;

            return ac <=> bc;
          }

          return std::strong_ordering::equal;
        });

      if (hey != std::strong_ordering::equal)
        return hey == std::strong_ordering::less;

      return std::lexicographical_compare(a.begin(), a.begin() + firstSpotA, b.begin(), b.begin() + firstSpotB);
    });

    return logs;
  }
};

int
main()
{
  return 0;
}
