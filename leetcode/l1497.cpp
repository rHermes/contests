#include <iostream>
#include <memory>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static bool canArrange(const std::vector<int>& arr, const int K)
  {
    // just because I can, I will use a static array here.
    auto freqs = std::make_unique<int[]>(K);

    for (const auto x : arr) {
      // this is faster than the general solution, as it avoids a second
      // divisor. On most hardware there will be no branch here
      int idx = x % K;
      if (idx < 0)
        idx += K;

      freqs[idx]++;
    }

    if (freqs[0] % 2 != 0)
      return false;

    for (int i = 1; i <= K / 2; i++) {
      if (freqs[i] != freqs[K - i])
        return false;
    }
    return true;
  }
};
