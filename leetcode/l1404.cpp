#include <algorithm>
#include <array>
#include <bit>
#include <cstdint>
#include <string>

class Solution
{
public:
  static constexpr int numSteps(const std::string& s)
  {
    if (s == "0")
      return 1;

    constexpr int MAXN = 8;

    // Let's treat this like it's an actual number.
    // We keep the MSB for indicating carry out.
    std::array<std::uint64_t, MAXN> bin{};
    int sz = 1;

    // We build the binary number.
    int cycle = 0;
    for (int i = s.size() - 1; 0 <= i; i--) {
      if (cycle == 63) {
        sz++;
        cycle = 0;
      }
      if (s[i] == '1') {
        bin[sz - 1] |= (1UL << cycle);
      }

      cycle++;
    }

    int steps = 0;
    while (bin[0] != 1 || std::ranges::any_of(bin.begin() + 1, bin.end(), [](const auto x) { return x != 0; })) {
      auto zeros = std::min(63, std::countr_zero(bin[0]));
      if (zeros) {
        steps += zeros;

        // ok, so now from the front we are going to shift things back.
        std::uint64_t overlap = 0;
        for (int i = MAXN - 1; 0 <= i; i--) {
          std::uint64_t new_overlap = bin[i] & ((1UL << zeros) - 1);
          new_overlap <<= 63 - zeros;
          bin[i] >>= zeros;
          bin[i] |= overlap;
          overlap = new_overlap;
        }

      } else {
        steps++;
        bool carry = 1;
        for (int i = 0; i < MAXN; i++) {
          carry = __builtin_add_overflow(carry, bin[i], &bin[i]);
        }
      }
    }

    return steps;
  }
};
