#include <algorithm>
#include <iostream>
#include <string>
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
  static int numSpecialEquivGroups(const std::vector<std::string>& words)
  {
    const int WS = words[0].size();
    std::unordered_set<std::size_t> num;

    std::string tmp(WS, 'a');
    for (auto& str : words) {
      int j = 0;
      for (int i = 0; i < WS; i += 2) {
        tmp[j++] = str[i];
      }
      int mid = j;

      for (int i = 1; i < WS; i += 2) {
        tmp[j++] = str[i];
      }

      // now we sort the first part.
      std::sort(tmp.begin(), tmp.begin() + mid);
      std::sort(tmp.begin() + mid, tmp.end());

      // Less copying around just using the hash.
      auto wew = std::hash<std::string>()(tmp);

      num.emplace(wew);
    }
    return num.size();
  }
};

int
main()
{
  return 0;
}
