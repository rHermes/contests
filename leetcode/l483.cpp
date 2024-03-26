#include <cstdint>
#include <numeric>
#include <optional>
#include <string>

class Solution {
public:
  // Here we are simply testing if the expansion of the base by nums are
  // bigger than N. We got to do this going down, since if we try to multiply
  // up, then we will always overflow.
  bool bigger(const std::uint64_t N, const std::uint8_t nums, const std::uint64_t base) {
    std::uint64_t cur = N - 1;

    for (std::uint8_t p = 2; p <= nums; p++) {
      cur /= base;
      if (cur == 0)
        return true;
      cur -= 1;
    }

    return false;
  }

  bool perfect(const std::uint64_t N, const std::uint8_t nums, const std::uint64_t base) {
    std::uint64_t cur = N - 1;

    for (std::uint8_t p = 2; p <= nums; p++) {
      if (cur % base != 0)
        return false;

      cur /= base;
      if (cur == 0)
        return false;
      cur -= 1;
    }

    return cur == 0;
  }

  std::optional<std::uint64_t> possible(const std::uint64_t N, const std::uint8_t nums) {
    std::uint64_t L = 2;
    std::uint64_t R = 1000000000000000000;

    if (bigger(N, nums, L))
      return std::nullopt;

    while (L + 1 < R) {
      const auto C = std::midpoint(L, R);

      if (bigger(N, nums, C))
        R = C;
      else
        L = C;
    }

    // ok, we now have to check if it's perfect.
    if (perfect(N, nums, L)) {
      return L;
    } else {
      return std::nullopt;
    }
  }

  std::string smallestGoodBase(std::string n) {
    const std::uint64_t N = std::stoull(n);

    for (std::uint8_t nums = 60; 2 < nums; nums--) {
      auto good = possible(N, nums);
      if (good)
        return std::to_string(*good);
    }

    // Worst case we just default to N-1.
    return std::to_string(N - 1);
  }
};

int main() { return 0; }
