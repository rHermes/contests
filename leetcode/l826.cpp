#include <algorithm>
#include <iostream>
#include <map>
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
  static int maxProfitAssignment(std::vector<int>& difficulty, std::vector<int>& profit, const std::vector<int>& worker)
  {
    const int N = difficulty.size();

    auto jobsSort = [&](const int i, const int j) {
      if (profit[i] != profit[j]) {
        return profit[i] > profit[j];
      }

      return difficulty[i] < difficulty[j];
    };

    std::vector<int> idx(N);
    std::iota(idx.begin(), idx.end(), 0);
    std::ranges::sort(idx, jobsSort);

    std::map<int, int> avail;
    for (const auto w : worker) {
      avail[w]++;
    }

    int ans = 0;
    int jIdx = 0;
    while (!avail.empty() && jIdx < N) {
      auto tp = idx[jIdx];

      const auto dif = difficulty[tp];

      auto it = avail.lower_bound(dif);
      if (it == avail.end()) {
        jIdx++;
        continue;
      }

      ans += profit[tp];
      if (--it->second == 0) {
        avail.erase(it);
      }
    }

    return ans;
  }
};
