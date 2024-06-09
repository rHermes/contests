#include <algorithm>
#include <iostream>
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
  static std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs)
  {
    std::unordered_map<std::string, std::vector<std::string>> data;
    std::string tmp;
    for (auto& str : strs) {
      tmp = str;
      std::ranges::sort(tmp);
      data[tmp].emplace_back(std::move(str));
    }

    std::vector<std::vector<std::string>> out;
    out.reserve(data.size());
    for (auto& it : data) {
      out.emplace_back(std::move(it.second));
    }

    return out;
  }
};
