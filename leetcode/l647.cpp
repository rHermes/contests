#include <string>
#include <vector>

class Solution
{
public:
  static int countSubstrings(const std::string& s)
  {
    const int N = s.size();
    std::vector<char> pal(N * N);
    int ans = 0;

    for (int i = 0; i < N; i++) {
      pal[i * N + i] = true;
      ans++;
    }

    for (int i = 0; i < N - 1; i++) {
      if (s[i] == s[i + 1]) {
        ans++;
        pal[i * N + i + 1] = true;
      }
    }

    for (int len = 2; len < N; len++) {
      for (int i = 0; i < N - len; i++) {
        if (s[i] == s[i + len] && pal[(i + 1) * N + (i + len - 1)]) {
          pal[i * N + (i + len)] = true;
          ans++;
        }
      }
    }

    return ans;
  }
};
