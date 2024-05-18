#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <vector>

using T = std::uint64_t;
constexpr int MAX_DIGITS = 11;

// Ah interesting. We also cannot have the first value overflowing.
// this means that the first digits are going to be very limited.

bool
inc(std::array<int, MAX_DIGITS>& num, int len)
{
  for (int i = len - 1; 0 <= i; i--) {
    if (num[i] == 9) {
      // we skip 0
      /* num[i] = 0; */
      num[i] = 1;
    } else {
      num[i]++;
      return true;
    }
  }
  return false;
}

void
cyclic(const int n)
{
  // Ok, so this is interesting, there are n possible uses here
  // the number cannot have 0 in it.

  std::array<int, MAX_DIGITS> lower{};
  for (int i = 0; i < n; i++)
    lower[i] = 1;

  // ok, I'm going to mutate the lower, until we arrive where we want.
  while (true) {
    // we are never going to be able to do it, if the front will over run.
    if (9 / n < lower.front())
      break;

    // now to multiply them together.
    // we create the 9 rotations.
    std::array<int, MAX_DIGITS> rots{};
    for (int offset = 0; offset < n; offset++) {
      int wow = 0;
      for (int j = 0; j < n; j++) {
        wow *= 10;
        wow += lower[(j + offset) % n];
      }
      rots[offset] = wow;
    }
    const int base = rots[0];

    // ok, now we have it, let's check.
    std::sort(std::begin(rots), std::next(rots.begin(), n));

    // ok, we check.
    bool good = true;
    int cur = base;
    for (int i = 2; i <= n; i++) {
      cur += base;
      if (!std::binary_search(rots.begin(), rots.begin() + n, cur)) {
        good = false;
        break;
      }
    }

    if (good) {
      for (int i = 0; i < n; i++)
        std::cout << lower[i];
      std::cout << "\n";
    }

    // let's just increment it.
    if (!inc(lower, n))
      break;
  }
}

int
main()
{
  // ok, so we are finding them post 8.
  // ok, first thought is just to brute force this, there are not that many numbers
  // and I imagine the iteration would be fast.
  for (int i = 1; i <= 8; i++)
    cyclic(i);

  return 0;
}
