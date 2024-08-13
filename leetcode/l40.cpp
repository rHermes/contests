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
  static constexpr void solve(std::vector<std::vector<int>>& out,
                              const std::array<int, 50 + 1>& freqs,
                              std::vector<int>& cur,
                              const int curIdx,
                              const int target)
  {
    if (target == 0) {
      out.emplace_back(cur);
      return;
    }

    if (target < curIdx)
      return;

    // Solve without using us.
    solve(out, freqs, cur, curIdx + 1, target);

    const auto fs = freqs[curIdx];
    const auto maxi = std::min(fs, target / curIdx);
    int curTarget = target;

    for (int i = 1; i <= maxi; i++) {
      curTarget -= curIdx;
      cur.push_back(curIdx);
      solve(out, freqs, cur, curIdx + 1, curTarget);
    }

    cur.erase(cur.end() - maxi, cur.end());
  }

public:
  static constexpr std::vector<std::vector<int>> combinationSum2(const std::vector<int>& candidates, int target)
  {
    std::array<int, 50 + 1> freqs{};
    for (const auto x : candidates) {
      freqs[x]++;
    }

    std::vector<std::vector<int>> out;
    std::vector<int> cur;
    solve(out, freqs, cur, 1, target);

    return out;
  }
};
