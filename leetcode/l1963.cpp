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
  static constexpr int minSwaps(const std::string& s)
  {
    const int N = s.size();
    int r = N - 1;
    while (s[r] != '[') {
      r--;
    }

    int ans = 0;
    int balance = 0;
    for (int l = 0; l < r; l++) {
      balance += (s[l] == '[') ? 1 : -1;
      if (balance < 0) {
        balance = 1;
        ans++;
        for (r--; l < r && s[r] != '['; --r) {
        }
      }
    }

    return ans;
  }
};
