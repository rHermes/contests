#include <array>
#include <cstdint>
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
  static constexpr bool checkInclusion(const std::string& s1, const std::string& s2)
  {
    const int N1 = s1.size();
    const int N2 = s2.size();
    if (N2 < N1) {
      return false;
    }

    std::array<std::int16_t, 26> seen{};

    // Add all characters from s1
    for (int i = 0; i < N1; i++)
      seen[s1[i] - 'a']++;

    // Remove the characters in the prefix of s2
    for (int i = 0; i < N1; i++)
      seen[s2[i] - 'a']--;

    // now we count the number of characters that are set
    char uniq = 0;
    for (int i = 0; i < 26; i++)
      uniq += seen[i] != 0;

    if (uniq == 0)
      return true;

    const auto popChar = [&](const int idx) {
      if (const auto ans = ++seen[idx]; ans == 0)
        uniq--;
      else if (ans == 1)
        uniq++;
    };

    const auto pushChar = [&](const int idx) {
      if (const auto ans = --seen[idx]; ans == 0) {
        return (--uniq) == 0;
      } else if (ans == -1) {
        uniq++;
      }
      return false;
    };

    for (int i = N1; i < N2; i++) {
      popChar(s2[i - N1] - 'a');
      if (pushChar(s2[i] - 'a'))
        return true;
    }

    return false;
  }
};
