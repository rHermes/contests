#include <array>
#include <limits>
#include <string>

class Solution
{
public:
  static constexpr int beautySum(const std::string& s)
  {
    using AT = std::array<int, 26>;
    const int N = s.size();

    constexpr auto score = [](const AT& arr) {
      int min = std::numeric_limits<int>::max();
      int max = std::numeric_limits<int>::lowest();
      for (const auto n : arr) {
        if (n == 0)
          continue;

        min = std::min(min, n);
        max = std::max(max, n);
      }
      return max - min;
    };

    AT cur{};
    int ans = 0;
    for (int r = 0; r < N; r++) {
      ++cur[s[r] - 'a'];
      ans += score(cur);

      AT temp = cur;
      for (int l = 0; l < r; l++) {
        --temp[s[l] - 'a'];
        ans += score(temp);
      }
    }

    return ans;
  }
};
