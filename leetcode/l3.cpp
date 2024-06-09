#include <bitset>
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
  static int lengthOfLongestSubstring(const std::string& s)
  {
    std::bitset<256> seen;

    int ans = 0;
    std::size_t l = 0;
    for (std::size_t r = 0; r < s.size(); r++) {
      const unsigned char c = s[r];
      while (seen[c]) {
        seen[s[l++]] = false;
      }
      seen[c] = true;

      ans = std::max(static_cast<int>(r - l + 1), ans);
    }

    return ans;
  }
};
