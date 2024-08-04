#include <string>

class Solution
{
public:
  static constexpr std::string removeKdigits(const std::string& num, const int k)
  {
    // Interesting. removing any one digit, both divides the number by 10
    // and that number.
    const int SN = num.size();
    if (SN <= k)
      return "0";

    int del = 0;
    std::string out;
    for (int i = 0; i < SN; i++) {
      // ok, so we need to remove the largest digits. That means we want a
      // continously growing integer.
      const char c = num[i];
      while (del < k && !out.empty() && c < out.back()) {
        out.pop_back();
        del++;
      }

      if (out.empty() && c == '0') {
        continue;
      }

      out.push_back(c);
    }

    while (!out.empty() && del < k) {
      del++;
      out.pop_back();
    }

    if (out.empty())
      out.push_back('0');

    return out;
  }
};
