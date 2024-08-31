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
  bool canReach(const std::vector<int>& arr, const int start)
  {
    const int N = arr.size();

    std::vector<bool> seen(N, false);
    seen[start] = true;

    std::vector<int> Q;
    Q.push_back(start);

    while (!Q.empty()) {
      const int cur = Q.back();
      Q.pop_back();

      if (arr[cur] == 0)
        return true;

      const int diff = arr[cur];
      if (0 <= cur - diff && !seen[cur - diff]) {
        seen[cur - diff] = true;
        Q.push_back(cur - diff);
      }

      if (cur + diff < N && !seen[cur + diff]) {
        seen[cur + diff] = true;
        Q.push_back(cur + diff);
      }
    }
    return false;
  }
};
