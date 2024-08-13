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
  static constexpr void solve(std::vector<std::vector<int>>& out,
                              const std::vector<int>& freqs,
                              std::vector<int>& cur,
                              const int curIdx,
                              const int target)
  {
    if (target == 0) {
      out.emplace_back(cur);
      return;
    }

    if (static_cast<int>(freqs.size()) <= curIdx)
      return;

    const auto curVal = freqs[curIdx];

    if (target < curVal)
      return;

    // Solve without using us.
    solve(out, freqs, cur, curIdx + 1, target);

    const auto maxi = target / curVal;
    int curTarget = target;

    for (int i = 1; i <= maxi; i++) {
      curTarget -= curVal;
      cur.push_back(curVal);
      solve(out, freqs, cur, curIdx + 1, curTarget);
    }

    cur.erase(cur.end() - maxi, cur.end());
  }

public:
  static constexpr std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target)
  {
    std::ranges::sort(candidates);

    std::vector<std::vector<int>> out;
    std::vector<int> cur;
    solve(out, candidates, cur, 0, target);
    return out;
  }
};
