#include <array>
#include <cstdint>
#include <string>
#include <vector>

// https://stackoverflow.com/questions/18644470/anagram-index-calculation/18646156#18646156

class Solution
{
  using ST = std::int64_t;
  static constexpr ST MODN = 1000000007;
  static constexpr int invMod(int a)
  {
    if (a <= 1) {
      return a;
    } else {
      return MODN - (ST)(MODN / a) * invMod(MODN % a) % MODN;
    }
  }

public:
  static int makeStringSorted(const std::string& s)
  {
    // interesting, the commands given are for finding the previous
    // lexiographical permutation. We can then find the index, by
    const int N = s.size();

    // This is the multiset actually which is very very nice.
    std::array<int, 26> freq{};
    for (const auto c : s) {
      freq[c - 'a']++;
    }

    std::vector<ST> frac(N + 1, 0);
    std::vector<ST> invFacs(N + 1, 0);
    frac[0] = 1;
    invFacs[0] = 1;
    for (int i = 1; i <= N; i++) {
      frac[i] = (static_cast<ST>(i) * frac[i - 1]) % MODN;
      invFacs[i] = (static_cast<ST>(invMod(i)) * invFacs[i - 1]) % MODN;
    }

    ST ans = 0;

    for (int charIdx = 0; charIdx < N; charIdx++) {
      const int sC = s[charIdx] - 'a';

      for (int prek = 0; prek < sC; prek++) {
        if (freq[prek] == 0) {
          continue;
        }

        const ST above = frac[N - charIdx - 1];

        freq[prek]--;
        ST below = 1;
        for (int pruk = 0; pruk < 26; pruk++) {
          below = (below * invFacs[freq[pruk]]) % MODN;
        }
        freq[prek]++;

        ans = (ans + above * below) % MODN;
      }

      --freq[sC];
    }

    return ans;
  }
};
