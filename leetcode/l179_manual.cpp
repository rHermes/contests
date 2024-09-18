#include <algorithm>
#include <array>
#include <charconv>
#include <iostream>
#include <memory>
#include <span>
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

    constexpr int MAXN = 10 * 100;
    std::array<char, MAXN> temp;

    auto partsRaw = std::make_unique_for_overwrite<std::span<char>[]>(N);
    auto parts = std::span(partsRaw.get(), partsRaw.get() + N);

    const auto endPtr = temp.data() + temp.size();
    auto curPtr = temp.data();
    for (int i = 0; i < N; i++) {
      const auto [ptr, ec] = std::to_chars(curPtr, endPtr, nums[i], 10);

      parts[i] = { curPtr, ptr };
      curPtr = ptr;
    }

    std::ranges::sort(parts, [](const auto& a, const auto& b) {
      const auto [end1, end2] = std::ranges::mismatch(a, b);

      if (end1 == a.end() && end2 == b.end()) {
        return false;
      } else if (end1 == a.end()) {
        const auto [end3, end4] = std::ranges::mismatch(b.begin(), b.end(), end2, b.end());
        if (end4 == b.end()) {
          return std::ranges::lexicographical_compare(a.begin(), a.end(), end3, b.end());
        } else {
          return *end4 < *end3;
        }
      } else if (end2 == b.end()) {
        const auto [end3, end4] = std::ranges::mismatch(end1, a.end(), a.begin(), a.end());
        if (end3 == a.end()) {
          return std::ranges::lexicographical_compare(end4, a.end(), b.begin(), b.end());
        } else {
          return *end4 < *end3;
        }
      } else {
        return *end2 < *end1;
      }
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
