#include <string>

class Solution
{
public:
  static constexpr bool isNumber(const std::string& s)
  {
    const int N = s.size();
    int idx = 0;

    const auto parseInteger = [&]() -> bool {
      int startPre = idx;
      while (idx < N && '0' <= s[idx] && s[idx] <= '9')
        idx++;

      return startPre != idx;
    };

    // 0 no digits
    // 1 digits
    // 2 error
    const auto parseNumber = [&]() -> unsigned char {
      if (s[idx] == '+' || s[idx] == '-')
        idx++;

      if (idx == N)
        return 2;

      return parseInteger();
    };

    const auto numsBeforeDot = parseNumber();
    if (numsBeforeDot == 2)
      return false;

    if (idx == N)
      return numsBeforeDot;

    if (s[idx] == '.') {
      idx++;
      if (idx == N) {
        return numsBeforeDot;
      }

      const bool numsAfterDot = parseInteger();
      if (!numsBeforeDot && !numsAfterDot) {
        return false;
      }
    } else {
      if (!numsBeforeDot) {
        return false;
      }
    }

    if (idx == N)
      return true;

    if (s[idx] != 'e' && s[idx] != 'E') {
      return false;
    }
    idx++;

    const auto numAfterExp = parseNumber();
    if (numAfterExp == 2) {
      return false;
    } else {
      return numAfterExp && idx == N;
    }
  }
};
