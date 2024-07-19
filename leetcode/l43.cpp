#include <string>

class Solution
{
public:
  static std::string multiply(const std::string& num1, const std::string& num2)
  {
    if (num1 == "0" || num2 == "0")
      return "0";

    // Let's try to do long multiplication here, as converting the
    // value back into base 10 will take longer than doing it the "normal"
    // way.

    const int N = num1.size();
    const int M = num2.size();

    std::string out(N + M, '0');

    for (int i = M - 1; 0 <= i; i--) {
      const int rg = num2[i] - '0';
      for (int j = N - 1; 0 <= j; j--) {
        const int lg = num1[j] - '0';

        const int mult = rg * lg;
        const int sum = mult + (out[j + i + 1] - '0');

        out[j + i] += sum / 10;
        out[j + i + 1] = (sum % 10) + '0';
      }
    }

    const auto firstGood = out.find_first_not_of('0');
    return out.substr(firstGood);
  }
};
