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
  static bool isPalindrome(const std::string& s, int l, int r)
  {
    while (l < r) {
      if (s[l++] != s[r--])
        return false;
    }

    return true;
  }

  static void dfs(const std::string& s,
                  std::vector<std::vector<std::string>>& out,
                  std::vector<std::string>& cur,
                  const int idx)
  {
    const int N = s.size();

    if (idx == N) {
      out.push_back(cur);
      return;
    }

    for (int j = idx; j < N; j++) {
      if (!isPalindrome(s, idx, j))
        continue;

      cur.emplace_back(s.substr(idx, j - idx + 1));
      dfs(s, out, cur, j + 1);
      cur.pop_back();
    }
  }

public:
  static std::vector<std::vector<std::string>> partition(const std::string& s)
  {
    std::vector<std::vector<std::string>> out;
    std::vector<std::string> tmp;
    dfs(s, out, tmp, 0);
    return out;
  }
};

int
main()
{
  return 0;
}
