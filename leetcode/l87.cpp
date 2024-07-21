#include <array>
#include <string>
#include <vector>

class Solution
{
  using BT = std::vector<unsigned char>;
  using CF = std::array<int, 26>;

  static constexpr bool solve(const int N,
                              const std::string_view& orig,
                              const std::string_view& scra,
                              BT& dp,
                              const int oStart,
                              const int sStart,
                              const int len)
  {
    int key = oStart * N * (N + 1) + sStart * N + len;
    if (dp[key]) {
      return dp[key] == 2;
    }

    // Let's look at the distribution within the entire thing then
    CF origF{};
    CF scraF{};
    for (int i = 0; i < len; i++) {
      const int oc = orig[oStart + i] - 'a';
      const int sc = scra[sStart + i] - 'a';

      origF[oc]++;
      scraF[sc]++;
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

    for (int i = 1; i < len; i++) {
      const int revLen = len - i;
      const int oSplit = oStart + i;
      const int sSplit = sStart + i;
      const int revSplit = sStart + revLen;

      // This is plain, split into x y and run on x and y
      const bool partA =
        solve(N, orig, scra, dp, oStart, sStart, i) && solve(N, orig, scra, dp, oSplit, sSplit, revLen);
      if (partA) {
        dp[key] = 2;
        return true;
      }

      // Now in this case we split it into x y and we want to run y x
      const bool partB =
        solve(N, orig, scra, dp, oStart, revSplit, i) && solve(N, orig, scra, dp, oSplit, sStart, revLen);
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

    // Due to the small length, we are not using a psa, but for longer
    // strings, this would be nececcary.
    BT seen(N * N * (N + 1), 0);
    return solve(N, orig, scrambled, seen, 0, 0, N);
  }
};
