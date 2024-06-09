#include <array>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  static constexpr std::array<std::string_view, 8> keys = { "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

public:
  static std::vector<std::string> letterCombinations(const std::string& digits)
  {
    if (digits.empty())
      return {};

    // We estimate the size, to minimize the number of reallocations.
    std::size_t len = 1;
    for (const auto d : digits) {
      len *= keys[d - '2'].size();
    }

    std::vector<std::string> out;
    out.reserve(len);
    for (const auto c : keys[digits[0] - '2']) {
      out.emplace_back(1, c);
    }

    for (std::size_t i = 1; i < digits.size(); i++) {
      const std::size_t len = out.size();
      const auto vw = keys[digits[i] - '2'];

      for (std::size_t j = 0; j < vw.size() - 1; j++) {
        for (std::size_t idx = 0; idx < len; idx++) {
          out.emplace_back(out[idx] + vw[j]);
        }
      }

      for (std::size_t idx = 0; idx < len; idx++) {
        out[idx] += vw.back();
      }
    }
    return out;
  }
};
