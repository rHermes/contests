// https://leetcode.com/problems/count-ways-to-build-rooms-in-an-ant-colony/
// https://codeforces.com/blog/entry/75627

#include <cstdint>
#include <iostream>
#include <vector>

using UT = std::int64_t;
constexpr UT MODN = 1000000007;

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

std::vector<int> facCache = { 1, 1 };
static int
facMod(int n)
{
  const int curSize = facCache.size();
  if (n < curSize)
    return facCache[n];

  facCache.resize(n + 1);
  for (UT i = curSize; i <= n; i++) {
    facCache[i] = (i * facCache[i - 1]) % MODN;
  }

  return facCache[n];
}

UT
invMod(UT a)
{
  if (a <= 1) {
    return a;
  } else {
    return MODN - (UT)(MODN / a) * invMod(MODN % a) % MODN;
  }
}

class Solution
{
  static std::pair<int, int> dfs(const std::vector<std::vector<int>>& G, const int cur)
  {
    UT ways = 1;
    UT totalLength = 0;
    UT smallLengths = 1;

    for (const auto next : G[cur]) {
      auto [cWays, cDepth] = dfs(G, next);
      ways = (ways * cWays) % MODN;
      totalLength += cDepth;
      smallLengths = (smallLengths * facMod(cDepth)) % MODN;
    }

    const UT finalAns = facMod(totalLength);
    const UT invBid = invMod(smallLengths);

    const UT waysPlain = (finalAns * invBid) % MODN;

    UT ans = (waysPlain * ways) % MODN;

    return { static_cast<int>(ans), 1 + totalLength };
  }

public:
  static int waysToBuildRooms(std::vector<int>& prevRoom)
  {
    const int N = prevRoom.size();
    std::vector<std::vector<int>> G(N);

    for (int i = 1; i < N; i++) {
      G[prevRoom[i]].push_back(i);
    }

    auto [ans, depth] = dfs(G, 0);
    return ans;
  }
};
;
