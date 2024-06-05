#include <array>
#include <iostream>
#include <limits>
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
  static std::vector<std::string> commonChars(const std::vector<std::string>& words)
  {
    std::array<int, 26> all;
    std::fill(all.begin(), all.end(), std::numeric_limits<int>::max());

    for (const auto& word : words) {
      std::array<int, 26> cur{};
      for (const auto c : word) {
        cur[c - 'a']++;
      }

      for (int i = 0; i < 26; i++) {
        all[i] = std::min(all[i], cur[i]);
      }
    }

    std::vector<std::string> out;
    for (int i = 0; i < 26; i++) {
      while (0 < all[i]--) {
        out.emplace_back(1, 'a' + i);
      }
    }

    return out;
  }
};

int
main()
{
  return 0;
}
