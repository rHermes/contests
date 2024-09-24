#include <algorithm>

class Solution
{
  static int countSteps(const int N, long prefix1, long prefix2)
  {
    int steps = 0;
    while (prefix1 <= N) {
      steps += std::min(static_cast<long>(N + 1), prefix2) - prefix1;
      prefix1 *= 10;
      prefix2 *= 10;
    }

    return steps;
  }

public:
  static int findKthNumber(const int N, const int K)
  {
    int curK = K - 1;
    int curR = 1;

    while (0 < curK) {
      int steps = countSteps(N, curR, curR + 1);
      if (steps <= curK) {
        curR++;
        curK -= steps;
      } else {
        curR *= 10;
        curK--;
      }
    }
    return curR;
  }
};
