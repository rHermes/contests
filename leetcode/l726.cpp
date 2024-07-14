#include <algorithm>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class Solution
{
  using AT = std::unordered_map<std::string_view, int>;

  static AT parse(std::string_view& str)
  {
    AT out;

    const auto readNum = [](std::string_view& s) {
      std::size_t sz = 0;
      int num = 0;
      while (sz < s.size() && '0' <= s[sz] && s[sz] <= '9') {
        num *= 10;
        num += s[sz] - '0';
        sz++;
      }

      if (num == 0) {
        return 1;
      } else {
        s.remove_prefix(sz);
        return num;
      }
    };

    while (!str.empty()) {
      if (str[0] == ')') {
        str.remove_prefix(1);
        return out;
      }

      if (str[0] == '(') {
        str.remove_prefix(1);
        auto childAtoms = parse(str);
        const auto times = readNum(str);

        for (const auto& [name, cnt] : childAtoms) {
          out[name] += times * cnt;
        }
        continue;
      }

      std::size_t sz = 1;
      while (sz < str.size() && 'a' <= str[sz] && str[sz] <= 'z') {
        sz++;
      }

      auto name = str.substr(0, sz);
      str.remove_prefix(sz);

      const auto times = readNum(str);
      out[name] += times;
    }

    return out;
  }

public:
  static std::string countOfAtoms(const std::string& formula)
  {
    std::string_view view = formula;
    auto atoms = parse(view);
    std::vector<std::pair<std::string_view, int>> outs;
    for (const auto& [k, v] : atoms) {
      outs.emplace_back(k, v);
    }
    std::ranges::sort(outs);

    std::string ans;
    for (const auto& [atom, val] : outs) {
      ans += atom;
      if (1 < val) {
        ans += std::to_string(val);
      }
    }

    return ans;
  }
};
