class Solution
{
public:
  static constexpr int minFlips(int a, int b, int c)
  {
    int ans = 0;
    while (0 < a || 0 < b || 0 < c) {
      bool aBit = a & 1;
      bool bBit = b & 1;
      bool cBit = c & 1;
      a >>= 1;
      b >>= 1;
      c >>= 1;

      if (cBit) {
        if (!aBit && !bBit)
          ans++;
      } else {
        if (aBit)
          ans++;

        if (bBit)
          ans++;
      }
    }

    return ans;
  }
};
