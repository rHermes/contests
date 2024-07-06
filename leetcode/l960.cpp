#include <iostream>
#include <map>
#include <string>
#include <vector>

class Solution
{
  using BT = std::vector<bool>;

  using ST = std::tuple<int, int, int, BT>;
  using CACHE = std::map<ST, int>;

  static int solve(const std::vector<std::string>& strs,
                   const int N,
                   const int SN,
                   CACHE& cache,
                   BT& masked,
                   const int curWord,
                   const int minCol,
                   const int lastCol,
                   const int inCurCol,
                   const int depth)
  {

    auto curCol = inCurCol;
    for (; curCol < SN && masked[curCol]; curCol++) {
    }

    const auto key = std::make_tuple(curWord, lastCol, curCol, masked);
    if (auto it = cache.find(key); it != cache.end())
      return it->second;

    const auto cacheIt = [&](int x) {
      cache.emplace(key, x);
      return x;
    };

    const auto beforeRet = [&](auto&& ret) {
      if (curWord != 0)
        return ret;

      for (int i = 0; i < depth; i++) {
        std::cout << ">";
      }

      std::cout << "solve( .cw = " << curWord << ", .mc = " << minCol << ", .lc = " << lastCol << ", .cc = " << curCol
                << ") = " << ret << ", ";
      std::cout << "Mask: [";
      for (const auto good : masked) {
        std::cout << (int)good;
      }
      std::cout << "]\n";
      return ret;
    };

    if (curWord == N) {
      return beforeRet(0);
    }

    if (curCol >= SN) {
      return beforeRet(cacheIt(solve(strs, N, SN, cache, masked, curWord + 1, minCol, minCol, minCol + 1, depth)));
    }

    if (curCol <= lastCol) {
      throw std::runtime_error("This should never happen");
    }

    if (masked[lastCol]) {
      throw std::runtime_error("This should never happen");
    }

    const auto& word = strs[curWord];
    const auto ac = word[lastCol];
    const auto bc = word[curCol];
    /*
    if (ac <= bc) {
        return beforeRet(solve(strs, N, SN, masked, curWord + 1, minCol,
    minCol, minCol + 1));
    }
    */
    if (ac <= bc) {
      return beforeRet(cacheIt(solve(strs, N, SN, cache, masked, curWord, minCol, curCol, curCol + 1, depth)));
    } else {
      masked[curCol] = true;
      int altA = 1 + solve(strs, N, SN, cache, masked, curWord, minCol, lastCol, curCol + 1, depth + 1);
      masked[curCol] = false;

      // We have a split. Either we delete this word or not.
      masked[lastCol] = true;
      int altB = [&] {
        if (lastCol == minCol) {
          int nextCol = minCol;
          while (nextCol < SN - 1 && masked[nextCol]) {
            nextCol++;
          }
          int nextLoc = std::max(nextCol + 1, curCol);

          return 1 + solve(strs, N, SN, cache, masked, curWord, nextCol, nextCol, nextLoc, depth + 1);

        } else {
          int prevPos = lastCol;
          while (masked[prevPos]) {
            prevPos--;
          }

          return 1 + solve(strs, N, SN, cache, masked, curWord, minCol, prevPos, curCol, depth + 1);
        }
      }();
      masked[lastCol] = false;

      return beforeRet(cacheIt(std::min(altA, altB)));
    }
  }

public:
  static int minDeletionSize(const std::vector<std::string>& strs)
  {
    // Hm It's not that long.
    const int N = strs.size();
    const int SN = strs.front().size();

    BT masked(SN, false);
    CACHE cache;
    return solve(strs, N, SN, cache, masked, 0, 0, 0, 1, 0);
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

  int ans = Solution::minDeletionSize(tc1);
  std::cout << "Solution: " << ans << "\n";

  return 0;
}
