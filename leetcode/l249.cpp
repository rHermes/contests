#include <iostream>
#include <string>
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
  static std::string minRemoveToMakeValid(std::string s)
  {
    std::vector<int> pars;
    pars.reserve(s.size());

    for (std::size_t i = 0; i < s.size(); i++) {
      const char c = s[i];

      if (c == '(') {
        pars.push_back(i);
      } else if (c == ')') {
        if (pars.empty()) {
          s.erase(i, 1);
          i--;
        } else {
          pars.pop_back();
        }
      }
    }

    while (!pars.empty()) {
      s.erase(pars.back(), 1);
      pars.pop_back();
    }

    return s;
  }
};

int
main()
{
  return 0;
}
