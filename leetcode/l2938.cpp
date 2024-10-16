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
  long long minimumSteps(const std::string& s)
  {
    const int N = s.size();

    long long ans = 0;
    int spot = 0;

    for (int i = 0; i < N; i++) {
      if (s[i] == '0') {
        ans += i - spot;
        spot++;
      }
    }

    return ans;
  }
};
