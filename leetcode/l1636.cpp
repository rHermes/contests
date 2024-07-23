#include <algorithm>
#include <iostream>
#include <unordered_map>
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
  static std::vector<int> frequencySort(std::vector<int>& nums)
  {
    std::unordered_map<int, int> freq{};
    for (const auto x : nums) {
      freq[x]++;
    }

    std::vector<std::pair<int, int>> pi;
    for (const auto& [i, f] : freq) {
      pi.emplace_back(f, i);
    }

    std::ranges::sort(pi, [](const auto& a, const auto& b) {
      if (auto cmp = a.first <=> b.first; cmp != 0) {
        return cmp < 0;
      }
      return b.second < a.second;
    });

    auto it = nums.begin();
    for (const auto& [f, i] : pi) {
      it = std::fill_n(it, f, i);
    }

    return std::move(nums);
  }
};
