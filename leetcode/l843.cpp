/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 */

#include <algorithm>
#include <array>
#include <numeric>
#include <string>
#include <vector>

class Master
{
public:
  int guess(std::string word) { return word == "hehe"; }
};

class Solution
{
public:
  void findSecretWord(const std::vector<std::string>& words, Master& master)
  {
    const int N = words.size();
    std::vector<std::vector<int>> dists(N, std::vector<int>(N, 0));
    std::vector<std::array<int, 7>> groups(N, std::array<int, 7>{});

    for (int i = 0; i < N; i++) {
      dists[i][i] = 6;
      groups[i][6]++;
      for (int j = i + 1; j < N; j++) {
        int same = 0;
        for (int k = 0; k < 6; k++) {
          if (words[i][k] == words[j][k])
            same++;
        }

        dists[i][j] = same;
        dists[j][i] = same;

        groups[i][same]++;
        groups[j][same]++;
      }
    }

    std::vector<int> pos(N);
    std::iota(pos.begin(), pos.end(), 0);

    auto end = pos.end();
    while (pos.begin() != end) {
      // we are going to minmax on the size of the group.

      int minMax = 1000000000;
      int ps = 0;

      for (auto it = pos.begin(); it != end; it++) {
        const auto hi = *it;
        auto heyMax = *std::ranges::max_element(groups[hi]);
        if (heyMax < minMax) {
          minMax = heyMax;
          ps = hi;
        }
      }

      int hits = master.guess(words[ps]);
      if (hits == 6)
        break;

      auto newEnd = std::partition(
        pos.begin(), end, [&](const auto& other) { return (other != ps) && (dists[ps][other] == hits); });

      // Now we update the tally for all new ones.
      for (auto it = pos.begin(); it != newEnd; it++) {
        const auto hi = *it;
        for (auto it2 = newEnd; it2 != end; it2++) {
          groups[hi][dists[hi][*it2]]--;
        }
      }
      end = newEnd;
    }
  }
};

int
main()
{
  return 0;
}
