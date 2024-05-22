class Solution
{
public:
  static double myPow(double x, int n)
  {
    // to avoid issues with -INT_MAX-1
    unsigned int nn = n;
    if (n < 0) {
      x = 1 / x;
      nn = -nn;
    }

    double res = 1;
    while (0 < nn) {
      if (nn & 1)
        res *= x;

      x *= x;
      nn >>= 1;
    }

    return res;
  }
};

int
main()
{
  return 0;
}
