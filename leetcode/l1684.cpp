#include <cstdint>
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
  static int countConsistentStrings(const std::string& allowed, const std::vector<std::string>& words)
  {
    std::uint32_t good = 0;
    for (const auto c : allowed) {
      good |= 1 << (c - 'a');
    }

    const std::uint32_t bad = ~good;

    int ans = 0;
    for (const auto& word : words) {
      std::uint32_t here = 0;
      for (const auto c : word) {
        here |= 1 << (c - 'a');
      }

      if ((bad & here) == 0) {
        ans++;
      }
    }
    return ans;
  }
};
