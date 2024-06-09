#include <charconv>
#include <cstdint>
#include <iostream>
#include <limits>
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
  static std::string nearestPalindromic(std::string n)
  {
    const auto N = n.size();
    if (N == 1) {
      if (n[0] == '0')
        return "1";
      else
        return { static_cast<char>(n[0] - 1) };
    }

    // Some other rules. If we have all 0, except 1, then we just return
    // the 999.. beneath
    if (n[0] == '1' && n.find_first_not_of('0', 1) == n.npos) {
      return std::string(N - 1, '9');
    }

    // if we are all 999999, then the one above is always going to win.
    if (n.find_first_not_of('9') == n.npos) {
      return "1" + std::string(N - 1, '0') + "1";
    }

    // We create the following lambda, to
    const auto orig = n;
    using T = std::int64_t;
    T nn;
    std::from_chars(n.data(), n.data() + n.size(), nn);

    T ansN = std::numeric_limits<T>::max();
    std::string ans;
    const auto newPos = [&]<typename U>(U&& str) {
      if (str == orig)
        return;

      T mm;
      std::from_chars(str.data(), str.data() + str.size(), mm);

      if (std::abs(ansN - nn) == std::abs(mm - nn)) {
        if (mm < ansN) {
          ansN = mm;
          ans = std::forward<U>(str);
        }
      } else if (std::abs(mm - nn) < std::abs(ansN - nn)) {
        ansN = mm;
        ans = std::forward<U>(str);
      }
    };

    for (std::size_t i = 0; i < N / 2; i++) {
      if (n[i] != n[N - 1 - i]) {
        n[N - 1 - i] = n[i];
      }
    }

    // options.emplace_back(n);
    newPos(n);
    newPos(std::string(N - 1, '9'));
    newPos("1" + std::string(N - 1, '0') + "1");

    // ok, we do a cheeky here, which is 9009;
    if (2 < N && n.find_first_not_of('0', 1) == N - 1) {
      std::string zeros(N, '0');
      std::string nines(N, '9');

      const char gg = n[0];

      for (char c = '1'; c <= '9'; c++) {
        if (c <= gg) {
          nines[0] = nines[N - 1] = c;
          newPos(nines);
        }
        if (gg <= c) {
          zeros[0] = zeros[N - 1] = c;
          newPos(zeros);
        }
      }
    }

    // if we are in a non zero, then that's is good.
    if (N % 2 != 0) {
      const auto center = N / 2;
      const char gg = n[center];
      for (char c = '0'; c <= '9'; c++) {
        if (c == gg)
          continue;

        n[center] = c;
        newPos(n);
      }
      n[center] = gg;
    } else {
      // We will move the center two.
      const auto center = N / 2 - 1;
      const char gg = n[center];
      for (char c = '0'; c <= '9'; c++) {
        if (c == gg)
          continue;

        n[center] = n[center + 1] = c;

        newPos(n);
      }
      n[center] = gg;
      n[center + 1] = gg;
    }

    return ans;
  }
};
