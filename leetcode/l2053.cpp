#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
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
  static std::string const kthDistinct(const std::vector<std::string>& arr, int k)
  {
    std::unordered_map<std::string_view, int> seen;
    for (const auto& s : arr) {
      seen[s]++;
    }

    for (const auto& s : arr) {
      if (seen[s] == 1) {
        if (--k == 0) {
          return s;
        }
      }
    }
    return "";
  }
};
