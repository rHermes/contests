#include <iostream>
#include <string>
#include <string_view>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static bool areSentencesSimilar(const std::string& s1, const std::string& s2)
  {
    const int SN1 = s1.size();
    const int SN2 = s2.size();

    if (SN1 == SN2) {
      return s1 == s2;
    } else if (SN2 < SN1) {
      return areSentencesSimilar(s2, s1);
    }

    // OK, so we are really just looking to get rid of the smallest one.
    // so we will first pop of all from the front that we can
    // and then all from the end.
    const std::string_view big = s2;
    const std::string_view small = s1;

    int leftPos = 0;
    while (leftPos != SN1) {
      auto nextSpace = small.find(' ', leftPos + 1);
      if (nextSpace == small.npos)
        nextSpace = SN1;

      if (big[nextSpace] != ' ')
        break;

      if (big.substr(leftPos, nextSpace - leftPos) != small.substr(leftPos, nextSpace - leftPos))
        break;

      leftPos = nextSpace;
    }
    if (leftPos == SN1)
      return true;

    if (leftPos == 0)
      return big[SN2 - SN1 - 1] == ' ' && big.ends_with(small);

    return big.ends_with(small.substr(leftPos));
  }
};
