#include <cstdint>

class Solution
{
public:
  static constexpr int countDigitOne(const int n)
  {
    std::int64_t numbersSoFar = 0;
    std::int64_t ans = 0;
    std::int64_t exp = 1;
    std::int64_t cum = 0;

    std::int64_t rest = n;
    while (0 < rest) {
      const int dig = rest % 10;
      if (dig == 1) {
        ans += (numbersSoFar + 1);
      }

      ans += dig * (cum);

      if (1 < dig) {
        ans += exp;
      }

      numbersSoFar += dig * exp;
      cum = exp + 10 * cum;

      exp *= 10;
      rest /= 10;
    }

    return ans;
  }
};

int
main()
{
  return 0;
}
