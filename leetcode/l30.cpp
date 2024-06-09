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
  static std::vector<int> findSubstring(const std::string& s, const std::vector<std::string>& words)
  {

    const int SN = s.size();
    const int NW = words.size();
    const int W = words[0].size();
    const int SUBLEN = NW * W;

    std::string_view view = s;

    std::unordered_map<std::string_view, int> base;
    for (const auto& lel : words) {
      base[lel]++;
    }

    std::vector<int> out;
    for (int offset = 0; offset < W; offset++) {
      if (SN < offset + SUBLEN)
        break;

      auto ws = base;
      int covered = base.size();

      int i = offset;
      for (; i <= offset + SUBLEN - W; i += W) {
        auto vw = ws.find(view.substr(i, W));
        if (vw == ws.end())
          continue;

        int times = --vw->second;
        if (times == 0) {
          covered--;
        }
      }
      if (covered == 0)
        out.emplace_back(offset);

      for (; i <= SN - W; i += W) {
        if (auto it = ws.find(view.substr(i - SUBLEN, W)); it != ws.end()) {
          if (++it->second == 1)
            covered++;
        }

        if (auto it = ws.find(view.substr(i, W)); it != ws.end()) {
          if (--it->second == 0)
            covered--;
        }

        if (covered == 0)
          out.emplace_back(i - SUBLEN + W);
      }
    }

    return out;
  }
};
