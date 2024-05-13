#include <cstdint>
#include <iostream>
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
  [[gnu::const, gnu::hot]] static int countPrimes(int n) noexcept
  {
    if (n < 3) {
      return 0;
    }

    std::vector<std::int8_t> prime(n, true);
    for (int i = 3; i * i <= n; i += 2) {
      if (!prime[i])
        continue;

      for (int kj = i * i; kj < n; kj += i) {
        prime[kj] = false;
      }
    }

    int ans = 1;
    for (int i = 3; i < n; i += 2) {
      ans += prime[i];
    }

    return ans;
  }
};

int
main()
{
  return 0;
}
