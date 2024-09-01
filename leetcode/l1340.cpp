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
  static int visit(const std::vector<int>& arr, const int N, const int D, std::vector<int>& cache, const int cur)
  {
    if (cache[cur] != -1) {
      return cache[cur];
    }

    int maxJump = 0;
    const int upperLimit = std::min(N, cur + D + 1);
    for (int idx = cur + 1; idx < upperLimit; idx++) {
      if (arr[cur] <= arr[idx])
        break;

      maxJump = std::max(maxJump, 1 + visit(arr, N, D, cache, idx));
    }

    const int lowerLimit = std::max(0, cur - D);
    for (int idx = cur - 1; lowerLimit <= idx; idx--) {
      if (arr[cur] <= arr[idx])
        break;

      maxJump = std::max(maxJump, 1 + visit(arr, N, D, cache, idx));
    }

    cache[cur] = maxJump;
    return maxJump;
  }

public:
  static int maxJumps(const std::vector<int>& arr, const int D)
  {
    // This can also be viewed as a graph problem, you can find my graph solution by looking at my
    // submissions on leetcode for this problem. It's a much more elegant solution than this, but
    // it's not faster than this, so we end up doing this just stupid memozation variant.
    const int N = arr.size();
    std::vector<int> cache(N, -1);

    int ans = 1;
    for (int i = 0; i < N; i++) {
      ans = std::max(ans, 1 + visit(arr, N, D, cache, i));
    }
    return ans;
  }
};
