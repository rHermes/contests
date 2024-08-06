#include <algorithm>
#include <array>
#include <iostream>
#include <string>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static constexpr int minimumPushes(const std::string& word)
  {
    std::array<int, 26> freqs{ 0 };
    for (const auto c : word) {
      freqs[c - 'a']++;
    }

    std::ranges::sort(freqs, std::ranges::greater{});

    int ans = 0;
    for (int i = 0; i < 26; i++) {
      ans += freqs[i] * (1 + (i / 8));
    }
    return ans;
  }
};
