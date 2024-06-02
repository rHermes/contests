#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
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
  static std::vector<std::string> findItinerary(const std::vector<std::vector<std::string>>& tickets)
  {
    std::vector<std::string_view> idx2names;
    std::unordered_map<std::string_view, int> name2idx;
    std::vector<std::vector<int>> G;

    const auto getIdx = [&](const std::string_view name) -> int {
      const auto [it, inserted] = name2idx.try_emplace(name, idx2names.size());
      if (!inserted) {
        return it->second;
      }

      idx2names.emplace_back(name);
      G.emplace_back();

      return it->second;
    };

    const auto jfkIdx = getIdx("JFK");

    // Now we create the graph.
    for (const auto& edge : tickets) {
      const auto src = getIdx(edge[0]);
      const auto dst = getIdx(edge[1]);

      G[src].push_back(dst);
    }

    for (auto& dsts : G) {
      std::ranges::sort(dsts, [&](const auto i, const auto j) { return idx2names[j] < idx2names[i]; });
    }

    // ok, now we have it, we can now begin.
    std::vector<int> stack{ jfkIdx };
    std::vector<int> path;

    while (!stack.empty()) {
      const auto cur = stack.back();

      if (G[cur].empty()) {
        path.push_back(cur);
        stack.pop_back();
      } else {
        stack.push_back(G[cur].back());
        G[cur].pop_back();
      }
    }

    // Now we convert back into names
    std::vector<std::string> out;
    out.reserve(path.size());
    for (auto it = path.rbegin(); it != path.rend(); it++) {
      out.emplace_back(idx2names[*it]);
    }
    return out;
  }
};

int
main()
{
  return 0;
}
