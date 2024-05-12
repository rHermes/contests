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
  static std::string longestPalindrome(const std::string& s)
  {
    const int N = s.size();

    int bestIdx = 0;
    int bestLen = 1;

    const auto expandSelection = [&](int l, int r) {
      while (0 < l && r < N - 1 && s[l - 1] == s[r + 1]) {
        l--;
        r++;
      }

      if (bestLen < (r - l + 1)) {
        bestIdx = l;
        bestLen = r - l + 1;
      }
    };

    for (int i = 0; i < N - 1; i++) {
      // we can exit early, if we are halfway there.
      if ((N - i) <= bestLen / 2)
        break;

      expandSelection(i, i);
      if (s[i] == s[i + 1])
        expandSelection(i, i + 1);
    }

    return s.substr(bestIdx, bestLen);
  }
};

int
main()
{
  return 0;
}
