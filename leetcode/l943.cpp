#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  static constexpr int MAXN = 12;

  static int getOverlap(const std::string& a, const std::string& b)
  {
    const int maxOverlap = std::min(a.size(), b.size());
    for (int overlap = maxOverlap; 0 <= overlap; overlap--) {
      const int shift = a.size() - overlap;

      bool good = true;
      for (int i = 0; i + shift < static_cast<int>(a.size()); i++) {
        if (a[i + shift] != b[i]) {
          good = false;
          break;
        }
      }

      if (good)
        return overlap;
    }

    return 0;
  }

public:
  std::string shortestSuperstring(const std::vector<std::string>& words)
  {
    const int N = words.size();
    const int KN = (1 << N);

    std::vector<int> overlaps(N * N, 0);

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        overlaps[i * N + j] = getOverlap(words[i], words[j]);
      }
    }

    std::vector<int> parent(KN * N, -1);
    std::vector<int> dp(KN * N, 0);

    for (int mask = 0; mask < KN; mask++) {
      for (int bit = 0; bit < N; bit++) {
        const int pmask = mask & (~(1 << bit));
        if (mask == pmask || pmask == 0)
          continue;

        for (int i = 0; i < N; i++) {
          if (!(pmask & (1 << i))) {
            continue;
          }

          int val = dp[pmask * N + i] + overlaps[i * N + bit];
          if (dp[mask * N + bit] < val) {
            dp[mask * N + bit] = val;
            parent[mask * N + bit] = i;
          }
        }
      }
    }

    // Ok, now we just have to find the
    int mask = KN - 1;
    int p = 0;
    for (int j = 0; j < N; j++) {
      if (dp[mask * N + p] < dp[mask * N + j])
        p = j;
    }

    // Now we know what the last element is, we are going to be following
    // that permutation down.
    std::vector<int> path;
    while (p != -1) {
      path.push_back(p);
      int next = parent[mask * N + p];
      mask ^= 1 << p;
      p = next;
    }
    // ok, now we have all the words with overlaps, but there might still be
    // someone left.
    std::ranges::reverse(path);

    // Fill in the last ones
    for (int bit = 0; bit < N; bit++) {
      if (mask & (1 << bit))
        path.push_back(bit);
    }

    // Now we can create the string.
    std::string out = words[path[0]];
    for (int i = 1; i < N; i++) {
      int overlap = overlaps[path[i - 1] * N + path[i]];
      out += words[path[i]].substr(overlap);
    }

    return out;
  }
};
