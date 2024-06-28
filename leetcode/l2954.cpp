#include <cstdint>
#include <vector>

using UT = std::int64_t;
constexpr UT MODN = 1000000007;

constexpr UT
expMod(UT base, UT exp)
{
  UT res = 1;
  base %= MODN;
  while (0 < exp) {
    if (exp % 2 == 1) {
      res = (res * base) % MODN;
    }

    exp >>= 1;
    base = (base * base) % MODN;
  }

  return res;
}

std::vector<UT> facCache = { 1, 1 };
UT
facMod(UT n)
{
  if (n < static_cast<UT>(facCache.size()))
    return facCache[n];

  UT prevSize = facCache.size();
  facCache.resize(n + 1);
  for (UT i = prevSize; i < n + 1; i++) {
    facCache[i] = (i * facCache[i - 1]) % MODN;
  }

  return facCache[n];
}

UT
invMod(UT a)
{
  if (a <= 1) {
    return a;
  } else {
    return MODN - (UT)(MODN / a) * invMod(MODN % a) % MODN;
  }
}

class Solution
{
public:
  static int numberOfSequence(const int n, const std::vector<int>& sick)
  {
    const int N = sick.size();

    UT numSeq = 1;
    UT numMergs = 1;
    UT curLength = 0;
    for (int i = 1; i < N; i++) {
      auto sz = sick[i] - sick[i - 1] - 1;
      numSeq = (numSeq * expMod(2, sz - 1)) % MODN;
      numMergs = (numMergs * facMod(sz)) % MODN;

      curLength += sz;
    }

    int L = sick.front();
    numMergs = (numMergs * facMod(L)) % MODN;
    curLength += L;

    int R = n - sick.back() - 1;
    numMergs = (numMergs * facMod(R)) % MODN;
    curLength += R;

    const UT totalSeqs = facMod(curLength);
    const UT finalMergs = (totalSeqs * invMod(numMergs)) % MODN;

    return (numSeq * finalMergs) % MODN;
  }
};
