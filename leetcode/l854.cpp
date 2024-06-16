#include <limits>
#include <string>

class Solution
{

  static int solve(const std::string& target, std::string& current, int from)
  {
    const int N = current.size();
    while (from < N && target[from] == current[from])
      from++;

    if (from == N)
      return 0;

    // If we can find do a two swap, that will be the answer.
    for (int to = from + 1; to < N; ++to) {
      if (current[to] != target[from] || current[from] != target[to])
        continue;

      // Ok, so we found our swap.
      std::swap(current[from], current[to]);
      int result = 1 + solve(target, current, from + 1);
      std::swap(current[from], current[to]);

      return result;
    }

    // Ok, now we need to compare all the possible 1 swaps and result the
    // best
    int ans = std::numeric_limits<int>::max();
    for (int to = from + 1; to < N; to++) {
      if (current[to] != target[from])
        continue;

      std::swap(current[from], current[to]);
      ans = std::min(ans, 1 + solve(target, current, from + 1));
      std::swap(current[from], current[to]);
    }
    return ans;
  }

public:
  static int kSimilarity(std::string& s1, const std::string& s2) { return solve(s2, s1, 0); }
};
