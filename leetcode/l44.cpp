#include <iostream>
#include <string>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static bool isMatch(const std::string& s, const std::string& p)
  {
    const auto PE = p.end();
    const auto SE = s.end();

    auto si = s.begin();
    auto pi = p.begin();

    auto star = PE;
    auto s_temp = SE;

    while (si != SE) {
      if (pi != PE && (*si == *pi || *pi == '?')) {
        si++;
        pi++;
      } else if (pi != PE && *pi == '*') {
        star = pi++;
        s_temp = si;
      } else if (star == PE) {
        return false;
      } else {
        pi = star + 1;
        si = ++s_temp;
      }
    }

    // We skip the last '*'
    while (pi != PE && *pi == '*')
      pi++;

    return pi == PE;
  }
};

int
main()
{
  return 0;
}
