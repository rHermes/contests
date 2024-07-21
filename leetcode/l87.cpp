#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

class Solution
{
  using BT = std::vector<unsigned char>;
  using CF = std::array<std::uint8_t, 26>;

  static constexpr bool solve(const int N,
                              const std::string_view& orig,
                              const std::string_view& scra,
                              const CF& origF,
                              const CF& scraF,
                              BT& dp,
                              const int oStart,
                              const int sStart,
                              const int len)
  {
    int key = oStart * N * (N + 1) + sStart * N + len;
    if (dp[key]) {
      return dp[key] == 2;
    }

    if (origF != scraF) {
      dp[key] = 1;
      return false;
    }

    // For anything less than 4 characters, we can create all
    // the permutations.
    if (len <= 3) {
      dp[key] = 2;
      return true;
    }

    auto upperOF = origF;
    auto upperSF = scraF;
    auto newLowerSF = scraF;

    CF lowerOF{};
    CF lowerSF{};
    CF newUpperSF{};

    for (int i = 1; i < len; i++) {
      const int revLen = len - i;
      const int oSplit = oStart + i;
      const int sSplit = sStart + i;
      const int revSplit = sStart + revLen;

      // Update the two lengths
      const auto oc = orig[oSplit - 1] - 'a';
      const auto sc = scra[sSplit - 1] - 'a';
      const auto nsc = scra[revSplit] - 'a';

      upperOF[oc]--;
      lowerOF[oc]++;

      upperSF[sc]--;
      lowerSF[oc]++;

      newLowerSF[nsc]--;
      newUpperSF[nsc]++;

      // This is plain, split into x y and run on x and y
      const bool partA = solve(N, orig, scra, lowerOF, lowerSF, dp, oStart, sStart, i) &&
                         solve(N, orig, scra, upperOF, upperSF, dp, oSplit, sSplit, revLen);
      if (partA) {
        dp[key] = 2;
        return true;
      }

      // Now in this case we split it into x y and we want to run y x
      const bool partB = solve(N, orig, scra, lowerOF, newUpperSF, dp, oStart, revSplit, i) &&
                         solve(N, orig, scra, upperOF, newLowerSF, dp, oSplit, sStart, revLen);
      if (partB) {
        dp[key] = 2;
        return true;
      }
    }

    dp[key] = 1;
    return false;
  }

public:
  static bool isScramble(const std::string& orig, const std::string& scrambled)
  {
    const int N = orig.size();

    // This is not strictly necessary for the lengths we are operating with,
    // but I like it better this way.
    CF origF{};
    CF scraF{};
    for (int i = 0; i < N; i++) {
      const int oc = orig[i] - 'a';
      const int sc = scrambled[i] - 'a';

      origF[oc]++;
      scraF[sc]++;
    }

    // Usual tribool,
    // 0 = unknown
    // 1 = false
    // 2 = true
    BT seen(N * N * (N + 1), 0);
    return solve(N, orig, scrambled, origF, scraF, seen, 0, 0, N);
  }
};
