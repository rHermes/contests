#include <algorithm>
#include <cstdint>
#include <limits>
#include <vector>

class Solution
{
public:
  static constexpr int nextGreaterElement(const int n)
  {
    std::vector<int> st;
    int cur = n;
    do {
      st.push_back(cur % 10);
      cur /= 10;
    } while (0 < cur);

    std::ranges::next_permutation(st.rbegin(), st.rend());

    std::int64_t ans = 0;
    for (auto it = st.rbegin(); it != st.rend(); it++) {
      ans *= 10;
      ans += *it;
      if (std::numeric_limits<int>::max() < ans)
        return -1;
    }

    if (ans <= n)
      return -1;

    return ans;
  }
};
