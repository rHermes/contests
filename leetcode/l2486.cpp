#include <iostream>
#include <string>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static constexpr int appendCharacters(const std::string& s, const std::string& t)
  {
    const int N = s.size();
    const int M = t.size();
    int gottem = 0;
    for (int i = 0; i < N; i++) {
      if (s[i] == t[gottem]) {
        gottem++;
        if (gottem == M)
          return 0;
      }
    }

    return M - gottem;
  }
};

int
main()
{
  return 0;
}
