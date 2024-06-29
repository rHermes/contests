#include <array>
#include <cstdint>

constexpr std::array<int, 50> ans = []() {
  const std::int64_t ROW = 56;
  std::array<std::int64_t, ROW * ROW> combs{};
  combs[0 * ROW + 0] = 1;
  for (int n = 1; n < ROW; n++) {
    combs[n * ROW + 0] = 1;
    combs[n * ROW + n] = 1;
    for (int k = 1; k < n; k++) {
      combs[n * ROW + k] = combs[(n - 1) * ROW + k - 1] + combs[(n - 1) * ROW + k];
    }
  }

  std::array<int, 50> work{};
  for (int i = 0; i < 50; i++) {
    work[i] = combs[(i + 1 + 4) * ROW + i + 1];
  }

  return work;
}();

class Solution
{
public:
  static constexpr int countVowelStrings(int n) { return ans[n - 1]; }
};
