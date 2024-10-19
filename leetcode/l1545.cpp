class Solution
{
public:
  char findKthBit(int n, int k)
  {
    bool invert = false;
    while (1 < n) {
      // ok, so which side of the line are we on?
      const int PN = (1 << (n - 1)) - 1;
      // std::cout << "We are in n=" << n << " and k=" << k << "\n";
      if (k <= PN) {
        // We are in the left side, we just progress down.
      } else if (k == PN + 1) {
        // we are exactly on the middle, we now know the exact method.
        return (invert) ? '0' : '1';
      } else {
        invert = !invert;
        k = 2 * (PN + 1) - k;
      }
      n--;
    }

    return (invert) ? '1' : '0';
  }
};
