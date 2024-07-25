#include <algorithm>
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
  static std::vector<int> sortJumbled(const std::vector<int>& mapping, std::vector<int>& nums)
  {
    const int N = nums.size();

    const auto convert = [&](int a) {
      int out = 0;
      int place = 1;
      do {
        out = place * mapping[a % 10] + out;
        place *= 10;
        a /= 10;
      } while (0 < a);

      return out;
    };

    std::vector<std::pair<int, int>> mapped(N);
    for (int i = 0; i < N; i++) {
      mapped[i] = { convert(nums[i]), nums[i] };
    }
    std::ranges::stable_sort(mapped, [](const auto& a, const auto& b) { return a.first < b.first; });
    for (int i = 0; i < N; i++) {
      nums[i] = mapped[i].second;
    }

    return std::move(nums);
  }
};
