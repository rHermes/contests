#include <algorithm>
#include <iostream>
#include <unordered_set>
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
  static long long findMaximumElegance(std::vector<std::vector<int>>& items, int k)
  {

    std::ranges::sort(items, std::greater{});

    // We keep one of each category here.
    std::unordered_set<int> biggest;
    std::vector<int> selected;
    selected.reserve(k);

    long long curAns = 0;
    for (int i = 0; i < k; i++) {
      auto itemProfit = items[i][0];
      auto itemCat = items[i][1];

      curAns += itemProfit;
      if (auto ins = biggest.emplace(itemCat); !ins.second)
        selected.emplace_back(itemProfit);
    }

    curAns += (biggest.size() * biggest.size());
    long long ans = curAns;

    const int N = items.size();
    for (int i = k; i < N; i++) {
      if (selected.empty() || static_cast<int>(biggest.size()) == k)
        break;
      // for each of these we check if we can insert it.
      auto itemProfit = items[i][0];
      auto itemCat = items[i][1];

      auto [it, inserted] = biggest.emplace(itemCat);
      if (!inserted)
        continue;

      // Update the current answer.
      curAns -= selected.back() - itemProfit;
      curAns += (biggest.size() - 1) * 2 + 1;
      selected.pop_back();

      ans = std::max(ans, curAns);
    }

    return ans;
  }
};
