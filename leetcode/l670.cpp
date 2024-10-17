#include <array>
#include <charconv>
#include <span>

class Solution
{
public:
  static int maximumSwap(const int num)
  {
    // ok, so it's always going to be to swap the largest number with the first number.
    // Max input is 10^8
    std::array<char, 9> buf;
    auto [ptr, _ec] = std::to_chars(buf.data(), buf.data() + buf.size(), num, 10);
    std::span<char> w{ buf.data(), ptr };

    const int SZ = w.size();
    [[assume(0 <= SZ && SZ < 9)]];

    int maxI = SZ - 1;
    int swapIdx1 = -1;
    int swapIdx2 = -1;

    for (int i = SZ - 2; 0 <= i; i--) {
      if (w[maxI] < w[i]) {
        maxI = i;
      } else if (w[i] < w[maxI]) {
        swapIdx1 = i;
        swapIdx2 = maxI;
      }
    }

    if (swapIdx1 != -1) {
      std::swap(w[swapIdx1], w[swapIdx2]);
    }

    int out = 0;
    for (const auto c : w) {
      out = 10 * out + static_cast<int>(c - '0');
    }
    return out;
  }
};
