#include <array>
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
  static constexpr int minLength(const std::string& s)
  {
    std::array<char, 102> st;
    st[0] = '.';

    int stIdx = 0;
    int ans = 0;

    const int N = s.size();
    for (int i = 0; i < N; i++) {
      const char c = s[i];
      if (c == 'A' || c == 'C') {
        st[++stIdx] = c;
      } else if (c == 'B' && st[stIdx] == 'A') {
        stIdx--;
      } else if (c == 'D' && st[stIdx] == 'C') {
        stIdx--;
      } else {
        ans += stIdx + 1;
        stIdx = 0;
      }
    }

    return stIdx + ans;
  }
};
