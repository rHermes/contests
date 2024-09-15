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

  // CharacterMap with the masks to flip the relevant states.
  static constexpr std::array<unsigned char, 26> characterMap = { 1, 0, 0, 0, 2, 0, 0, 0,  4, 0, 0, 0, 0,
                                                                  0, 8, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0 };

public:
  static constexpr int findTheLongestSubstring(const std::string& s)
  {
    const int N = s.size();

    // We know that there are only 32 possible states here, so we
    // Just store when each of them appear for the first time.
    std::array<int, 32> firstSeen;
    std::ranges::fill(firstSeen, -1);

    unsigned char state = 0;
    firstSeen[state] = 0;

    int ans = 0;
    for (int i = 0; i < N; i++) {
      state ^= characterMap[s[i] - 'a'];

      if (firstSeen[state] < 0) {
        firstSeen[state] = i + 1;
      } else {
        ans = std::max(ans, i + 1 - firstSeen[state]);
      }
    }

    return ans;
  }
};
