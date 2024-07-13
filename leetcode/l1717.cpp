#include <iostream>
#include <utility>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static constexpr int maximumGain(const std::string& s, int x, int y)
  {
    char aChar = 'a';
    char bChar = 'b';

    if (x < y) {
      std::swap(aChar, bChar);
      std::swap(x, y);
    }

    int ans = 0;

    int countA = 0;
    int countB = 0;

    for (const auto c : s) {
      if (c == aChar) {
        countA++;
      } else if (c == bChar) {
        // If we have A, we use it to make B
        if (0 < countA) {
          countA--;
          ans += x;
        } else {
          // We save it for further ba creation.
          countB++;
        }
      } else {
        // ok, a clearance, we now make the best out of it and create as
        // many ba's as we can
        ans += y * std::min(countA, countB);
        countA = 0;
        countB = 0;
      }
    }

    ans += y * std::min(countA, countB);

    return ans;
  }
};
