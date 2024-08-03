#include <algorithm>
#include <array>
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
  static constexpr bool canBeEqual(const std::vector<int>& target, const std::vector<int>& arr)
  {
    std::array<int, 1000> digs{};
    for (const auto x : target) {
      digs[x - 1]++;
    }

    for (const auto x : arr) {
      digs[x - 1]--;
    }

    return std::ranges::all_of(digs, [](const int x) { return x == 0; });
  }
};
