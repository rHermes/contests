#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static std::string shortestPalindrome(const std::string& s)
  {
    using T = std::int64_t;
    const int N = s.size();

    constexpr T MODN = 1000000007;
    constexpr T PRIME = 31; // java uses this, so we use this.

    // OK, so this is actually much easier than I thought. We just have to
    // check if we at any point can make a palindrom from the beginning. We
    // will simply keep two rolling hashes, one from the beginning in the
    // reverse and one from the beginning in the other direction. if they
    // match we are good.

    T hLeft = 0;
    T hRight = 0;
    T p = 1;

    int len = 0;

    for (int i = 0; i < N; i++) {
      hLeft = (hLeft + p * s[i]) % MODN;
      p = (p * PRIME) % MODN;

      hRight = (PRIME * hRight + s[i]) % MODN;

      if (hLeft == hRight) {
        len = i + 1;
      }
    }
    if (len == N)
      return s;

    // Let's see here.
    const int tailLen = (N - len);
    const int totalLen = tailLen + N;

#if __cpp_lib_string_resize_and_overwrite >= 202110L
    std::string out;
    out.resize_and_overwrite(totalLen, [&](char* p, std::size_t) noexcept -> std::size_t {
      std::ranges::copy_n(s.rbegin(), tailLen, p);
      std::ranges::copy_n(s.begin(), totalLen, p + tailLen);
      return totalLen;
    });
#else
    std::string out(totalLen, '\0');
    auto it = std::ranges::copy_n(s.rbegin(), tailLen, out.begin()).out;
    std::ranges::copy(s, it);
#endif

    return out;
  }
};
