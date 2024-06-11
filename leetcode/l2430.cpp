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
  static int deleteString(const std::string& s)
  {

    // The approach here, is that we are going to use a rolling hash, where we view the hash as a
    // digit in base 31. This allows us select out parts of that digit, by using a normal PSA and
    // dividing by the power of the base on the leftmost digit.
    using T = std::int64_t;
    const int N = s.size();
    constexpr T MODN = 1000000007;
    constexpr T PRIME = 31;            // java uses this, so we use this.
    constexpr T INV_PRIME = 129032259; // This is the inverse of 31

    // We create a stupid hash function.
    std::vector<T> PSA(N + 1);
    std::vector<T> INV(N + 1);

    INV[0] = 1;

    T inv = 1;
    T p = 1;

    bool allSame = true;
    for (int i = 0; i < N; i++) {
      if (s[0] != s[i])
        allSame = false;

      PSA[i + 1] = (PSA[i] + s[i] * p) % MODN;
      INV[i + 1] = inv;

      p = (p * PRIME) % MODN;
      inv = (inv * INV_PRIME) % MODN;
    }

    if (allSame)
      return N;

    std::vector<int> dp(N + 1, -1);

    dp[0] = 0;
    for (int l = 0; l < N; l++) {
      if (dp[l] == -1) {
        continue;
      }

      dp[N] = dp[l] + 1;

      for (int i = 1; i <= (N - l) / 2; i++) {

        T leftHash = (PSA[l + i] - PSA[l] + MODN) % MODN;
        leftHash = (leftHash * INV[l + 1]) % MODN;

        T rightHash = (PSA[l + i + i] - PSA[l + i] + MODN) % MODN;
        rightHash = (rightHash * INV[l + i + 1]) % MODN;

        if (leftHash == rightHash) {
          // In real life we would do a comparison here, but the
          // input has not been crafted against us, so this works.
          dp[l + i] = dp[l] + 1;
        }
      }
    }

    return dp[N];
  }
};
