#include <numeric>
#include <vector>

class Solution
{
public:
  static int findTheWinner(const int n, const int k)
  {
    std::vector<int> next(n);
    std::iota(next.begin(), next.end(), 1);
    next.back() = 0;

    int last = n - 1;
    int pos = 0;

    for (int r = 0; r < n - 1; r++) {
      const int sz = n - r;
      const int steps_right = (k - 1) % sz;

      for (int i = 0; i < steps_right; i++) {
        last = pos;
        pos = next[pos];
      }

      // Remove the current node.
      pos = next[pos];
      next[last] = pos;
    }

    return pos + 1;
  }
};
