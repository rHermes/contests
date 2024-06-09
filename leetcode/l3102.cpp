#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
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
public:
  static int minimumDistance(const std::vector<std::vector<int>>& points)
  {
    // We can just maintain a queue and check each point.
    const int N = points.size();

    // Let's create a convex hull then.
    std::vector<int> indices(N);
    std::iota(indices.begin(), indices.end(), 0);
    std::ranges::sort(indices, [&](const auto a, const auto b) { return points[a] < points[b]; });

    const auto cross = [&](const int oi, const int ai, const int bi) {
      const auto& O = points[indices[oi]];
      const auto& A = points[indices[ai]];
      const auto& B = points[indices[bi]];
      return static_cast<std::int64_t>(A[0] - O[0]) * (B[1] - O[1]) <=
             static_cast<std::int64_t>(A[1] - O[1]) * (B[0] - O[0]);
    };

    // ok, now to create the lower hull first..
    std::vector<int> hull;
    for (int i = 0; i < N; i++) {
      while (1 < hull.size() && cross(hull[hull.size() - 2], hull.back(), i))
        hull.pop_back();

      hull.push_back(i);
    }
    const int lowerSize = hull.size();
    const std::size_t lowerSizeSz = lowerSize;

    for (int i = N - 2; 0 <= i; i--) {
      while (lowerSizeSz < hull.size() && cross(hull[hull.size() - 2], hull.back(), i))
        hull.pop_back();

      hull.push_back(i);
    }

    // We remove the last, as it will be a duplicate
    hull.pop_back();
    const int M = hull.size();

    // Ok, now we find the node pair with the largest distance.
    // if there is more than 1 root node that has this, we are screwed.

    std::array<int, 2> bestNodes{ -1, -1 };
    int maxDist = -1;
    for (int i = 0; i < M; i++) {
      const auto& a = points[indices[hull[i]]];

      int thisDist = 0;
      int thisBest = 0;
      for (int j = i + 1; j < M; j++) {
        const auto& b = points[indices[hull[j]]];
        int dist = std::abs(a[0] - b[0]) + std::abs(a[1] - b[1]);

        if (thisDist < dist) {
          thisDist = dist;
          thisBest = j;
        }
      }

      if (thisDist == maxDist) {
        bestNodes[0] = -1;
        if (bestNodes[1] != i && bestNodes[1] != thisBest)
          bestNodes[1] = -1;
      } else if (maxDist < thisDist) {
        bestNodes[0] = i;
        bestNodes[1] = thisBest;
        maxDist = thisDist;
      }
    }

    const auto removeHull = [&](const int target) -> int {
      std::vector<int> newHull;
      if (target == 0) {
        newHull.push_back(hull[M - 2]);
        newHull.push_back(hull[M - 1]);
      } else if (target == 1) {
        newHull.push_back(hull[M - 1]);
        newHull.push_back(hull[0]);
      } else {
        newHull.push_back(hull[target - 2]);
        newHull.push_back(hull[target - 1]);
      }
      const int preSize = 2;

      if (target == 0) {
        for (int i = hull[M - 1] - 1; 1 <= i; i--) {

          while (preSize < newHull.size() && cross(newHull[newHull.size() - 2], newHull.back(), i))
            newHull.pop_back();

          newHull.push_back(i);
        }

        const std::size_t preTwo = newHull.size();
        for (int i = 1; i <= hull[1]; i++) {
          while (preTwo < newHull.size() && cross(newHull[newHull.size() - 2], newHull.back(), i)) {
            newHull.pop_back();
          }

          newHull.push_back(i);
        }
      } else if (target == lowerSize - 1) {
        for (int i = hull[target - 1] + 1; i < N - 1; i++) {
          while (preSize < newHull.size() && cross(newHull[newHull.size() - 2], newHull.back(), i)) {
            newHull.pop_back();
          }

          newHull.push_back(i);
        }

        const std::size_t preTwo = newHull.size();

        const int end = (lowerSize == M) ? 0 : hull[lowerSize];

        for (int i = N - 2; end <= i; i--) {
          while (preTwo < newHull.size() && cross(newHull[newHull.size() - 2], newHull.back(), i))
            newHull.pop_back();

          newHull.push_back(i);
        }
      } else if (target < lowerSize) {
        for (int i = newHull.back() + 1; i <= hull[target + 1]; i++) {
          if (i == hull[target])
            continue;

          while (preSize < newHull.size() && cross(newHull[newHull.size() - 2], newHull.back(), i)) {
            newHull.pop_back();
          }

          newHull.push_back(i);
        }
      } else {
        for (int i = newHull.back() - 1; 0 <= i; i--) {
          if (i == hull[target])
            continue;

          while (preSize < newHull.size() && cross(newHull[newHull.size() - 2], newHull.back(), i)) {
            newHull.pop_back();
          }

          newHull.push_back(i);
        }
      }
      newHull.pop_back();

      int maxAns = 0;
      for (std::size_t i = preSize; i < newHull.size(); i++) {
        const auto& a = points[indices[newHull[i]]];

        for (int j = 0; j < M; j++) {
          if (j == target)
            continue;

          const auto& b = points[indices[hull[j]]];
          int dist = std::abs(a[0] - b[0]) + std::abs(a[1] - b[1]);
          maxAns = std::max(maxAns, dist);
        }
      }

      return maxAns;
    };

    if (bestNodes[1] == -1) {
      return maxDist;
    }

    int maxAns0 = 0;
    int maxAns1 = 0;

    for (int i = 0; i < M; i++) {
      const auto& a = points[indices[hull[i]]];
      for (int j = i + 1; j < M; j++) {
        const auto& b = points[indices[hull[j]]];
        int dist = std::abs(a[0] - b[0]) + std::abs(a[1] - b[1]);

        if (i != bestNodes[0] && j != bestNodes[0]) {
          maxAns0 = std::max(maxAns0, dist);
        }
        if (i != bestNodes[1] && j != bestNodes[1]) {
          maxAns1 = std::max(maxAns1, dist);
        }
      }
    }

    if (bestNodes[0] == -1) {
      return std::max(maxAns1, removeHull(bestNodes[1]));
    } else {
      int a0 = std::max(maxAns0, removeHull(bestNodes[0]));
      int a1 = std::max(maxAns1, removeHull(bestNodes[1]));
      return std::min(a0, a1);
    }
  }
};
