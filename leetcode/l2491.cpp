#include <array>
#include <iostream>
#include <numeric>
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
  static long long dividePlayers(const std::vector<int>& skill)
  {
    const int N = skill.size();
    const int teams = N / 2;

    int totalSkill = std::reduce(skill.begin(), skill.end());

    if (totalSkill % teams != 0)
      return -1;
    const int teamSkill = totalSkill / teams;

    const int lowerLimit = teamSkill - 1000;
    std::array<int, 1001> has{};
    for (const auto x : skill) {
      if (x < lowerLimit || teamSkill <= x)
        return -1;

      has[x]++;
    }

    long long ans = 0;

    int l = std::max(1, teamSkill - 1000);
    int r = teamSkill - l;
    long long chem = l * r;

    while (l < r) {
      if (has[l] != has[r]) {
        return -1;
      }

      ans += has[l] * chem;

      // By updating it like this, we avoid doing a multiplicaton each step.
      chem += r - l - 1;
      l++;
      r--;
    }

    // We have to account for the fact that if there is a centeral postion,
    // it must only be counted once.
    if (l == r) {
      if (has[l] % 2 != 0) {
        return -1;
      }

      ans += (has[l] / 2) * chem;
    }

    return ans;
  }
};
