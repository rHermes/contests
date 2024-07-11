#include <algorithm>
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
  static std::string reverseParentheses(const std::string& s)
  {
    std::vector<int> openPos;
    std::string out;

    const int N = s.size();
    for (int i = 0; i < N; i++) {
      if (s[i] == '(') {
        openPos.push_back(out.size());
      } else if (s[i] == ')') {
        auto beg = openPos.back();
        openPos.pop_back();
        std::reverse(out.begin() + beg, out.end());
      } else {
        out.push_back(s[i]);
      }
    }

    return out;
  }
};
