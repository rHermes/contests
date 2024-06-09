#include <array>
#include <vector>

class Solution
{

public:
  static int maxCoins(const std::vector<int>& nums)
  {
    // The key here is to consider what would happen if this was the last
    // ballon we popped. If that was the case, then the two problems to the
    // left and right of us would essentially become independent problems.
    //
    // We keep l and r to keep track of the limit of the current problem. If
    // we go outside the bounds, then we will use 1.
    //
    // We do a bottom up apporach here, by considering each length in
    // increasing order.

    const int N = nums.size();
    const int NN = N + 1;

    std::array<int, 302 * 302> dp;

    // we only need to initialize these, no other for now.
    for (int i = 0; i < NN; i++)
      dp[i * NN + i] = 0;

    for (int len = 1; len <= N; ++len) {
      // Now then we are going to do each of these.
      for (int left = 0; left <= N - len; left++) {
        const int right = left + len;
        const int ll = (left == 0) ? 1 : nums[left - 1];
        const int rr = (right == N) ? 1 : nums[right];

        const int ourMult = ll * rr;

        int ans = 0;
        for (int x = left; x < right; x++) {
          ans = std::max(ans, ourMult * nums[x] + dp[left * NN + x] + dp[(x + 1) * NN + right]);
        }

        dp[left * NN + right] = ans;
      }
    }
    return dp[0 * NN + N];
  }
};
