#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{

  using GRAPH = std::vector<std::vector<int>>;

  static constexpr int dfs(const GRAPH& G,
                           const std::vector<int>& nums,
                           const int target,
                           const int parent,
                           const int cur)
  {
    std::int64_t sum = nums[cur];

    for (const auto next : G[cur]) {
      if (next == parent)
        continue;

      sum += dfs(G, nums, target, cur, next);
      if (target < sum)
        return std::numeric_limits<int>::max();
    }

    return (sum == target) ? 0 : sum;
  }

  static constexpr int tryAllPrimes(const int numSum,
                                    const GRAPH& G,
                                    const std::vector<int>& nums,
                                    const std::vector<std::pair<int, int>>& primes,
                                    const int soFar,
                                    const int curIdx)
  {
    if (curIdx == -1) {
      const int target = numSum / soFar;
      if (dfs(G, nums, target, -1, 0) == 0)
        return soFar - 1;
      else
        return 0;
    }

    const auto [prime, cnt] = primes[curIdx];
    int cur = soFar;
    for (int i = 0; i <= cnt; i++) {
      const int res = tryAllPrimes(numSum, G, nums, primes, cur, curIdx - 1);
      if (0 < res) {
        return res;
      }

      cur /= prime;
    }

    return 0;
  }

public:
  static constexpr int componentValue(const std::vector<int>& nums, const std::vector<std::vector<int>>& edges)
  {
    const int N = nums.size();
    const int numSum = std::reduce(nums.begin(), nums.end(), 0);

    GRAPH G(N);
    for (const auto& edge : edges) {
      const auto a = edge[0];
      const auto b = edge[1];
      G[a].push_back(b);
      G[b].push_back(a);
    }

    auto primes = primeFactor(N, numSum);

    return tryAllPrimes(numSum, G, nums, primes, numSum, primes.size() - 1);
  }

private:
  static constexpr std::vector<std::pair<int, int>> primeFactor(const int N, const int target)
  {
    // Let's get all the primes up to N, which is the maximum number of
    // parts we can split it into
    const int maxPrime = static_cast<int>(std::sqrt(N)) + 1;

    // The max prime we want to test is N
    // because primes above that, is not interesting to us.

    std::vector<unsigned char> isComp(maxPrime + 1);
    std::vector<std::pair<int, int>> primes;

    int curTarget = target;
    for (int i = 2; i <= maxPrime; i++) {
      if (isComp[i])
        continue;

      if (curTarget < i) {
        break;
      }

      int times = 0;
      while (i <= curTarget && (curTarget % i == 0)) {
        times++;
        curTarget /= i;
      }
      if (0 < times) {
        primes.emplace_back(i, times);
      }

      for (int j = i + i; j <= maxPrime; j += i) {
        isComp[j] = true;
      }
    }

    if (1 < curTarget) {
      primes.emplace_back(curTarget, 1);
    }

    return primes;
  }
};
