#include <iostream>
#include <string>

class Solution
{
public:
  static constexpr int minAddToMakeValid(const std::string& s)
  {
    int ans = 0;
    int bal = 0;
    for (const auto c : s) {
      if (c == '(') {
        bal++;
      } else {
        bal--;
        if (bal < 0) {
          ans++;
          bal = 0;
        }
      }
    }

    return ans + bal;
  }
};
