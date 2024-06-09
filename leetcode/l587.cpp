#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

// https://usaco.guide/plat/convex-hull?lang=cpp

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static std::vector<std::vector<int>> outerTrees(const std::vector<std::vector<int>>& trees)
  {
    const int N = trees.size();
    if (N < 4) {
      return trees;
    }

    // We do the usual song and dance, with sorting an index array, to avoid the swapping of
    // the trees.
    std::vector<int> indices(N);
    std::iota(indices.begin(), indices.end(), 0);
    std::ranges::sort(indices, [&](const auto a, const auto b) { return trees[a] < trees[b]; });

    const auto cross = [&](const int oi, const int ai, const int bi) {
      const auto& O = trees[oi];
      const auto& A = trees[ai];
      const auto& B = trees[bi];
      return (A[0] - O[0]) * (B[1] - O[1]) - (A[1] - O[1]) * (B[0] - O[0]);
    };

    std::vector<int> hull;
    hull.reserve(N);

    // Now we are going to build the lower hull
    for (int i = 0; i < N; i++) {
      while (1 < hull.size() && cross(hull[hull.size() - 2], hull.back(), indices[i]) < 0) {
        hull.pop_back();
      }

      hull.emplace_back(indices[i]);
    }

    const auto lowSize = hull.size();

    // Now then, we know that the one most right and up must be a part too.
    for (int i = N - 2; 0 <= i; i--) {
      while (lowSize < hull.size() && cross(hull[hull.size() - 2], hull.back(), indices[i]) < 0) {
        hull.pop_back();
      }

      hull.emplace_back(indices[i]);
    }

    // remove the duplicate last position
    hull.pop_back();

    // The only time the end of the upper hull and the start of the lower hull will be the same,
    // is if we are simply a flat line. In that case we simply remove the upper hull.
    if (hull[1] == hull.back()) {
      hull.resize(lowSize);
    }

    // finally, create the output
    std::vector<std::vector<int>> output(hull.size());
    for (std::size_t i = 0; i < hull.size(); i++)
      output[i] = trees[hull[i]];

    return output;
  }
};
