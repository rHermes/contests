#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  using ST = std::int64_t;
  static constexpr ST MODN = 1000000007;

  static constexpr int invMod(int a)
  {
    if (a <= 1) {
      return a;
    } else {
      return MODN - (ST)(MODN / a) * invMod(MODN % a) % MODN;
    }
  }

  using GRAPH = std::unordered_map<int, std::pair<int, int>>;

  static std::pair<int, int> solve(const GRAPH& G,
                                   const std::vector<int>& facs,
                                   const std::vector<int>& invFacs,
                                   const int root)
  {
    // ok, so this is rather easy actually.
    auto it = G.find(root);
    const auto [lNode, rNode] = it->second;
    if (lNode == -1 && rNode == -1) {
      return { 1, 1 };
    } else if (lNode == -1) {
      auto [cWays, cDepth] = solve(G, facs, invFacs, rNode);
      return { cWays, cDepth + 1 };
    } else if (rNode == -1) {
      auto [cWays, cDepth] = solve(G, facs, invFacs, lNode);
      return { cWays, cDepth + 1 };
    }

    const auto [lWays, lDepth] = solve(G, facs, invFacs, lNode);
    const auto [rWays, rDepth] = solve(G, facs, invFacs, rNode);

    // Now here is the thing. Each side can be done in
    // x ways. This means that we have a total of
    // lWays * rWays combinations.
    const auto xWays = (static_cast<ST>(lWays) * rWays) % MODN;

    auto waysToMerge = (static_cast<ST>(facs[lDepth + rDepth]) * invFacs[lDepth]) % MODN;
    waysToMerge = (waysToMerge * invFacs[rDepth]) % MODN;

    const auto totalWays = (waysToMerge * xWays) % MODN;

    return { totalWays, 1 + lDepth + rDepth };
  }

public:
  static int numOfWays(const std::vector<int>& nums)
  {
    // Ok, let's first construct the binary tree, which is really just a
    // normal tree. We always need the parent to have been inserted.
    const int N = nums.size();

    std::vector<int> facs(N + 1);
    facs[0] = 1;
    facs[1] = 1;
    std::vector<int> invFacs(N + 1);
    invFacs[0] = 1;
    invFacs[1] = 1;

    for (int i = 2; i <= N; i++) {
      facs[i] = (static_cast<ST>(i) * facs[i - 1]) % MODN;
      invFacs[i] = (static_cast<ST>(invMod(i)) * invFacs[i - 1]) % MODN;
    }

    // Build the binary tree
    GRAPH G;

    // Root first.
    G[nums.front()] = { -1, -1 };

    for (int i = 1; i < N; i++) {
      auto curNode = nums.front();
      const auto val = nums[i];

      while (true) {
        auto& [l, r] = G[curNode];
        if (val < curNode) {
          if (l == -1) {
            l = val;
            G[val] = { -1, -1 };
            break;
          } else {
            curNode = l;
          }
        } else {
          if (r == -1) {
            r = val;
            G[val] = { -1, -1 };
            break;
          } else {
            curNode = r;
          }
        }
      }
    }

    auto [ans, num] = solve(G, facs, invFacs, nums.front());
    return (ans - 1 + MODN) % MODN;
  }
};
