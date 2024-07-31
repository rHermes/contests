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
  static constexpr int countSeniors(const std::vector<std::string>& details)
  {
    return std::ranges::count_if(details, [](const std::string& det) {
      const char first = det[11];
      if (auto cmp = first <=> '6'; cmp != 0) {
        return 0 < cmp;
      }

      return '0' < det[12];
    });
  }
};
