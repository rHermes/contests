#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

constexpr std::int64_t MODN = 1000000007;
constexpr std::int64_t MODINV = 500000004;
inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static int sumSubseqWidths(std::vector<int>& nums)
  {
    const int N = nums.size();

    std::ranges::sort(nums);

    std::vector<int> pow2(N);
    pow2[0] = 1;
    std::int64_t cans = 2;
    for (int i = 1; i < N; i++) {
      pow2[i] = (pow2[i - 1] + cans) % MODN;
      cans = (cans * 2) % MODN;
    };

    cans = 2;
    for (int i = 1; i < N; i++) {
      nums[i] = (nums[i - 1] + cans * nums[i]) % MODN;
      cans = (cans * 2) % MODN;
    }

    std::int64_t ans = 0;
    std::int64_t inver = MODINV;
    for (int l = 0; l < N - 1; l++) {
      std::int64_t prev = (l == 0) ? 0 : nums[l - 1];
      std::int64_t upper = nums.back() - nums[l];
      upper = (upper * inver) % MODN;

      // ok, so now upper are of the right order.
      std::int64_t elems = N - 1 - l;

      std::int64_t less = nums[l] - prev;
      less = (less * inver * 2) % MODN;
      less = (less * pow2[elems - 1]) % MODN;

      upper = (upper - less) % MODN;
      ans = (ans + upper) % MODN;

      inver = (inver * MODINV) % MODN;
    }
    return (ans + MODN) % MODN;
  }
};

int
main()
{
  return 0;
}
