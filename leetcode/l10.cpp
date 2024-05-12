#include <array>
#include <iostream>
#include <string>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

enum class TriBool : unsigned char
{
  Undefined,
  False,
  True,
};

class Solution
{
  static constexpr int ROW = 21;
  using DPT = std::array<TriBool, ROW * ROW>;
  static TriBool canMatch(DPT& dp, const std::string& s, const std::string& p, std::size_t i, std::size_t j)
  {
    const auto key = ROW * i + j;
    if (dp[key] != TriBool::Undefined) {
      return dp[key];
    }

    const bool canSkip = j < p.size() - 1 && p[j + 1] == '*';

    if (s.size() == i && canSkip) {
      dp[key] = canMatch(dp, s, p, i, j + 2);
      return dp[key];
    }

    if (s.size() == i || p.size() == j) {
      dp[key] = TriBool::False;
      return dp[key];
    }

    const char sc = s[i];
    const char pc = p[j];

    if (canSkip) {
      auto ans = canMatch(dp, s, p, i, j + 2);
      if (ans == TriBool::True) {
        dp[key] = ans;
        return dp[key];
      }
    }

    if (pc != sc && pc != '.') {
      dp[key] = TriBool::False;
      return dp[key];
    }

    if (canSkip) {
      dp[key] = canMatch(dp, s, p, i + 1, j + 2);
      if (dp[key] == TriBool::False) {
        dp[key] = canMatch(dp, s, p, i + 1, j);
      }

    } else {
      dp[key] = canMatch(dp, s, p, i + 1, j + 1);
    }

    return dp[key];
  }

public:
  static bool isMatch(const std::string& s, const std::string& p)
  {
    DPT dp{};
    dp[s.size() * ROW + p.size()] = TriBool::True;

    return canMatch(dp, s, p, 0, 0) == TriBool::True;
  }
};
int
main()
{
  return 0;
}
