#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Solution
{
public:
  static int minDeletionSize(const std::vector<std::string>& strs)
  {
    const int SN = strs.front().size();

    // We are just looking things up.
    std::vector<unsigned char> lessArr(SN * SN, true);
    for (int i = 0; i < SN; i++) {
      for (int j = i; j < SN; j++) {
        for (const auto& word : strs) {
          if (word[j] < word[i]) {
            lessArr[i * SN + j] = false;
            break;
          }
        }
      }
    }

    /* for (const auto& word : strs) { */
    /*   for (int i = 0; i < SN; i++) { */
    /*     for (int j = i; j < SN; j++) { */
    /*       lessArr[i * SN + j] &= word[i] <= word[j]; */
    /*       /1* lessArr[j * SN + i] &= word[j] <= word[i]; *1/ */
    /*     } */
    /*   } */
    /* } */

    const auto lessThan = [&](const int a, const int b) -> bool { return lessArr[a * SN + b]; };

    std::vector<int> d(SN, 1);
    for (int i = 0; i < SN; i++) {
      for (int j = 0; j < i; j++) {
        if (lessThan(j, i)) {
          d[i] = std::max(d[i], d[j] + 1);
        }
      }
    }

    return SN - std::ranges::max(d);
  }
};

int
main()
{
  std::vector<std::string> tc1 = {
    "deehdecfcgegffegghfhfaagcaaffbfahcfaghgdfggbbddbff", "dchhgcbahdbdgbbaafhbgfggcbebfacdebhfgcfaafcgbgbggg",
    "hehdggagfabdfbhegebhaaddcaghhegeegdgegagehhdhheecd", "fhbbagbdffedafacbeahddbgagggdafceeabaffhhhhcedcfbh",
    "caaefgdgefeahcgfgccaacdfabdgdbdhdbhbhfadbeaegbbdce", "habgbahaeebeacccbdhfhddegfebheeffdbcbgfahhgbhcheeb",
    "gfaaedgcachcehgdghebbhegbfagdgcdcgebddbdccbedbbhcd", "badaebdbdgeadbfgchaegaddgdhdgaeaaedagacgbdecfdghca",
    "eefcceffcggeefbecaceadbdcfccgbfgffgahfgeebafdcfhhb", "aeebdahabfecbafgbcchbhdeecaadaccbahghcbdcfaeagehha"
  };

  std::vector<std::string> tc2 = { "aabbaa", "baabab", "aaabab" };

  std::vector<std::string> tc3 = { "cbbdabc" };

  std::vector<std::string> tc4 = { "agbfeegaageagabaebgehghhdfffddedhhfcbefahdegfghdahhhdhabghdc",
                                   "cceagbeefgaegbabdgbccfeahbfaaceehdhceegdbbgfebhcaaghefegcfee",
                                   "bgbeefgcbaeadfhebbbaecgbfghbfbhgcdbaaahgggecfceafdhdagbbfafc",
                                   "ghfecceceeeacfabhbecbhheddafeegahhhabccbhcfaffhfhbhaeddcgbch",
                                   "dbddhhdcadefbaaehhchhcfegbdfhahgbhddgbdagfahcahgbbhggehfhaff",
                                   "abadgggafehedbbgccbfcfaceaddaadcaddedhfddaffhgeccegbcdfecfeh",
                                   "acefhgcdhbhdafhddeddbahdbbecgdhahfafgcehbeebeeegfdechfcbabhg",
                                   "ccfgfbhceacbeaedaeehhebgedbfgcehgdhbdgcfbhchfgaddfhfbgchbdeh",
                                   "deggafecaeaefhgdgfgafagabbfffebfhhcbcafaeebbbbfegfacgeabbgeb",
                                   "agcbdeccdeadafgeddadfggchbfgadgcdbgcfcfbdchdcagdfhfgdbghhhgb" };
  int ans = Solution::minDeletionSize(tc3);
  std::cout << "Solution: " << ans << "\n";

  // What is the longest increasing subsequence I can build across multiple series?
  return 0;
}
