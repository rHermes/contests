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
  static std::vector<int> findOrder(int numCourses, const std::vector<std::vector<int>>& prerequisites)
  {
    std::vector<int> counts(numCourses);
    std::vector<std::vector<int>> children(numCourses);

    for (const auto& edge : prerequisites) {
      const int from = edge[1];
      const int to = edge[0];

      counts[to]++;
      children[from].push_back(to);
    }

    std::vector<int> Q;
    for (int i = 0; i < numCourses; i++) {
      if (counts[i] == 0) {
        Q.push_back(i);
      }
    }
    std::vector<int> ans;
    ans.reserve(numCourses);

    while (!Q.empty()) {
      auto cur = Q.back();
      Q.pop_back();

      ans.push_back(cur);

      for (const auto& to : children[cur]) {
        if (--counts[to] == 0)
          Q.push_back(to);
      }
    }

    if (ans.size() == static_cast<std::size_t>(numCourses))
      return ans;
    else
      return {};
  }
};
