#include <iostream>
#include <numeric>
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
  static std::string fractionAddition(const std::string& exp)
  {
    const int N = exp.size();
    int i = 0;

    auto parseFrac = [&]() {
      bool pos = true;
      if (i != 0) {
        pos = exp[i] == '+';
        i++;
      } else {
        if (exp[i] == '-') {
          pos = false;
          i++;
        }
      }

      int num = 0;
      int den = 0;

      while (exp[i] != '/') {
        num *= 10;
        num += exp[i] - '0';
        i++;
      }

      i++;

      while (i < N && exp[i] != '+' && exp[i] != '-') {
        den *= 10;
        den += exp[i] - '0';
        i++;
      }

      if (!pos) {
        num = -num;
      }

      return std::make_pair(num, den);
    };

    int num = 0;
    int den = 1;

    auto normalize = [&] {
      if (num == 0) {
        num = 0;
        den = 1;
      } else {
        auto d = std::gcd(num, den);
        num /= d;
        den /= d;
      }
    };

    // ok, here we have the actual parsing loop.
    while (i < N) {
      auto [curNom, curDen] = parseFrac();
      num = (num * curDen + curNom * den);
      den = (den * curDen);
      normalize();
    }

    return std::to_string(num) + "/" + std::to_string(den);
  }
};
