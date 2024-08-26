#include <algorithm>
#include <iostream>
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
  static int longestWPI(const std::vector<int>& hours)
  {
    // ok, so first of what can I do here to speed this up?
    // OK, let's do something cheeky.
    const int N = hours.size();

    std::vector<int> PSA(N + 1, 0);
    for (int i = 0; i < N; i++) {
      PSA[i + 1] = PSA[i] + 1 - 2 * (hours[i] <= 8);
    }

    // ok, so by definition, we are now just trying to find the largest pair of
    // l, r in PSA, where l < r and PSA[l] < PSA[r]. Now how do we find that
    // interval.
    //
    // We do this in the following, by exploiting that if l1 < l2 and PSA[l1] < PSA[l2],
    // then if l2 < r and PSA[l2] < PSA[r], then we will also have l1 < r and PSA[l1] < PSA[r].
    // This means that we first just build up a montonic decreasing stack, of all the lowest points
    // in the series, going from left to right. We can then go from right to left and just pop elements
    // as long as They are smaller than the current element. This will by definition be the biggest interval
    // where PSA[l] < PSA[r].

    // 0 we always be at 0, so we implicitly include it.
    std::vector<int> stk{ 0 };
    for (int l = 1; l <= N; l++) {
      if (PSA[l] < PSA[stk.back()]) {
        stk.push_back(l);
      }
    }

    int ans = 0;
    for (int r = N; 0 <= r; r--) {
      while (!stk.empty() && PSA[stk.back()] < PSA[r]) {
        // ok, so now we are in a spot where the PSA overall is growing.
        // meaning that from stk.back() to r there was an increase.
        ans = std::max(ans, r - stk.back());
        stk.pop_back();
      }
    }

    return ans;
  }
};
