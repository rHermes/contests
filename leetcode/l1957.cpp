#include <string>

class Solution
{
public:
  static std::string makeFancyString(std::string s)
  {
    const int N = s.size();
    if (N < 3)
      return s;

    // This is greedy I think? For 3x characters, we don't need it.
    int pos = 2;
    char lastChar = s[1];
    bool noMore = s[0] == s[1];

    for (int i = 2; i < N; i++) {
      const char c = s[i];

      if (c != lastChar) {
        s[pos++] = c;
        noMore = false;
        lastChar = c;
      } else {
        if (!noMore) {
          noMore = true;
          s[pos++] = c;
        }
      }
    }

    s.resize(pos);
    return s;
  }
};
