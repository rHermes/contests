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
  static constexpr int nthUglyNumber(int n)
  {
    // ok, let's create a queue.
    std::vector<std::pair<long long, int>> ops;
    ops.emplace_back(1, 0);

    constexpr std::array<long long, 3> facs{ 2, 3, 5 };

    for (int i = 1; i < n; i++) {
      const auto [cur, idx] = ops.front();
      std::ranges::pop_heap(ops, std::ranges::greater{});
      ops.back() = { cur * facs[idx], idx };
      std::ranges::push_heap(ops, std::ranges::greater{});

      // ok, so we have x, we need:
      for (int j = idx + 1; j < 3; j++) {
        ops.emplace_back(cur * facs[j], j);
        std::ranges::push_heap(ops, std::ranges::greater{});
      }
    }

    // Now we have the one.
    const auto& [ans, idx] = ops.front();
    return ans;
  }
};
