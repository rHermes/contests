#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>
#include <unordered_map>
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
  static std::vector<std::string> alertNames(const std::vector<std::string>& keyName,
                                             const std::vector<std::string>& keyTime)
  {
    std::vector<int> indexes(keyName.size());
    std::iota(indexes.begin(), indexes.end(), 0);

    std::sort(indexes.begin(), indexes.end(), [&](const int i, const int j) { return keyTime[i] < keyTime[j]; });

    // Workers, we are just going to keep the last 3 for each.
    constexpr auto parseTime = [](const std::string& a) {
      int hours = (a[0] - '0') * 10 + (a[1] - '0');
      int minutes = (a[3] - '0') * 10 + (a[4] - '0');

      return hours * 60 + minutes;
    };

    std::unordered_set<std::string_view> out;

    std::unordered_map<std::string_view, std::tuple<int, int, int>> db;
    for (std::size_t i = 0; i < indexes.size(); i++) {
      const auto idx = indexes[i];
      if (out.count(keyName[idx]))
        continue;

      auto [it, itOK] = db.emplace(keyName[idx], std::forward_as_tuple<int, int, int>(-100, -100, -100));
      const auto [ign, b, c] = it->second;
      const auto d = parseTime(keyTime[idx]);

      if ((d - b) <= 60) {
        out.emplace(it->first);
      }

      it->second = std::tie(b, c, d);
    }

    std::vector<std::string> ans(std::make_move_iterator(out.begin()), std::make_move_iterator(out.end()));
    std::sort(ans.begin(), ans.end());

    return ans;
  }
};

int
main()
{
  return 0;
}
