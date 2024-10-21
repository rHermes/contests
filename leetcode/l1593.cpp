#include <string>
#include <string_view>
#include <unordered_set>

class Solution
{
  int solve(std::string_view prefix, std::unordered_set<std::string_view>& seen)
  {
    if (prefix.empty())
      return 0;

    int N = prefix.size();
    int ans = -1;

    for (int i = 1; i <= N; i++) {
      // We just break as soon as we can. This is massive for runtime
      if ((N - i) <= ans)
        break;

      auto [it, inserted] = seen.emplace(prefix.substr(0, i));
      if (!inserted)
        continue;

      ans = std::max(ans, solve(prefix.substr(i), seen));

      seen.erase(it);
    }

    return ans + 1;
  }

public:
  int maxUniqueSplit(const std::string& s)
  {
    std::unordered_set<std::string_view> seen;

    return solve(s, seen);
  }
};
