#include <cstdint>
#include <iostream>
#include <vector>

class Solution
{
public:
  static int totalStrength(const std::vector<int>& strength)
  {
    constexpr std::int64_t MOD = 1000000007;

    // Let's create a utopia people.
    const int N = strength.size();
    std::vector<int> left(N, -1);
    std::vector<int> right(N, N);

    std::vector<std::pair<int, int>> stk;
    for (int i = 0; i < N; i++) {
      const auto str = strength[i];
      while (!stk.empty() && str <= stk.back().second) {
	stk.pop_back();
      }

      if (!stk.empty()) {
	left[i] = stk.back().first;
      }

      stk.emplace_back(i, str);
    }

    // calculate the right side
    stk.clear();
    for (int i = N - 1; 0 <= i; i--) {
      const auto str = strength[i];
      while (!stk.empty() && str < stk.back().second) {
	stk.pop_back();
      }

      if (!stk.empty()) {
	right[i] = stk.back().first;
      }

      stk.emplace_back(i, str);
    }

    // ok, now we need to run a double PSA over this one.
    std::vector<std::int32_t> PSA(N + 1);
    for (int i = 1; i <= N; i++) {
      PSA[i] = (PSA[i - 1] + strength[i - 1]) % MOD;
    }

    std::vector<std::int32_t> PSAA(N + 2);
    for (int i = 1; i <= N + 1; i++) {
      PSAA[i] = (PSAA[i - 1] + PSA[i - 1]) % MOD;
    }

    // Ok, now we are ready for the finaly.
    std::int64_t ans = 0;
    for (int i = 0; i < N; i++) {
      // ok, we check left and right
      const auto l = left[i] + 1;
      const auto r = right[i] - 1;

      const auto positiveParts = (((PSAA[r + 2] - PSAA[i + 1]) % MOD) * ((i - l + 1) % MOD)) % MOD;
      const auto negativeParts = (((PSAA[i + 1] - PSAA[l]) % MOD) * ((r - i + 1) % MOD)) % MOD;

      // Every subsequence involving us has this.
      const std::int64_t totSum = (positiveParts - negativeParts + MOD) % MOD;
      ans                       = ans + (totSum * strength[i]) % MOD;
      ans %= MOD;
    }

    return ans;
  }
};

static const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

int
main()
{
  return 0;
}
