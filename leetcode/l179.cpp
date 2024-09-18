#include <algorithm>
#include <charconv>
#include <iostream>
#include <ranges>
#include <span>
#include <string>
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
  static std::string largestNumber(const std::vector<int>& nums)
  {
    const int N = nums.size();

    // A temporary spot to store the nums while building.
    std::array<char, 10 * 100> temp;

    std::vector<std::span<char>> parts(N);

    const auto endPtr = temp.data() + temp.size();
    auto curPtr = temp.data();

    for (int i = 0; i < N; i++) {
      const auto [ptr, ec] = std::to_chars(curPtr, endPtr, nums[i], 10);

      parts[i] = { curPtr, ptr };
      curPtr = ptr;
    }

    std::ranges::sort(parts, [](const auto& a, const auto& b) {
      const auto opt1 = { a, b };
      const auto opt2 = { b, a };

      return std::ranges::lexicographical_compare(std::views::join(opt2), std::views::join(opt1));
    });

    if (parts[0][0] == '0') {
      return "0";
    }

    std::string out(std::distance(temp.begin(), curPtr), 'A');
    auto outIt = out.begin();
    for (const auto& part : parts) {
      outIt = std::ranges::copy(part, outIt).out;
    }

    return out;
  }
};
