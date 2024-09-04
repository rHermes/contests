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
public:
  static std::string findLongestWord(const std::string& s, const std::vector<std::string>& dictionary)
  {
    const int N = s.size();
    std::string ans = "";

    for (const auto& word : dictionary) {
      const int W = ans.size();
      const int M = word.size();

      // Before doing a scan of the string, we are going to make sure
      // it's worth searching.
      if (M < W || (M == W && ans <= word))
        continue;

      int idx = 0;
      for (int i = 0; i < N; i++) {
        if (s[i] == word[idx]) {
          if (++idx == M)
            break;
        }
      }

      if (idx == M)
        ans = word;
    }

    return ans;
  }
};
