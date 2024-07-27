#include <array>
#include <cstdint>
#include <string>

class Solution
{
public:
  static constexpr std::string removeDuplicateLetters(const std::string& s)
  {
    using BT = std::uint32_t;

    // Let's see if there isn't something we can do here.
    const int N = s.size();

    std::array<int, 26> lastIndex;
    for (int i = 0; i < N; i++) {
      lastIndex[s[i] - 'a'] = i;
    }

    std::string out;
    out.reserve(26);
    BT seen{ 0 };

    for (int i = 0; i < N; i++) {
      const char c = s[i];
      const int ic = (c - 'a');
      const int bic = 1 << ic;

      if (seen & bic)
        continue;

      while (!out.empty() && c < out.back() && i < lastIndex[out.back() - 'a']) {
        seen ^= 1 << (out.back() - 'a');
        out.pop_back();
      }

      seen |= bic;
      out.push_back(c);
    }

    return out;
  }
};
