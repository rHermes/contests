#include <iostream>
#include <limits>
#include <string>
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
  static std::vector<std::string> findRestaurant(const std::vector<std::string>& list1,
                                                 const std::vector<std::string>& list2)
  {
    std::unordered_map<std::string_view, int> pos1;
    for (int i = 0; i < static_cast<int>(list1.size()); i++) {
      pos1[list1[i]] = i;
    }

    std::vector<std::string> out;
    int minIndex = std::numeric_limits<int>::max();
    for (int i = 0; i < static_cast<int>(list2.size()); i++) {
      const auto& cur = list2[i];
      auto it = pos1.find(cur);
      if (it == pos1.end())
        continue;

      int dist = i + it->second;
      if (dist < minIndex) {
        out.clear();
        out.emplace_back(cur);
        minIndex = dist;

      } else if (dist == minIndex) {
        out.emplace_back(cur);
      }
    }

    return out;
  }
};
