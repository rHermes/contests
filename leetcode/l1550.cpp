#include <vector>

class Solution
{
public:
  bool threeConsecutiveOdds(const std::vector<int>& arr)
  {
    int cur = 0;
    for (const auto& x : arr) {
      if (x & 1) {
        if (3 == ++cur) {
          return true;
        }
      } else {
        cur = 0;
      }
    }

    return false;
  }
};
