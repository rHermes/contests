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
  static std::string convert(const std::string& s, const int numRows)
  {
    if (numRows == 1)
      return s;

    const int N = s.size();
    // we should instead just do this directly.
    std::string out(N, 'X');

    int idx = 0;
    int STEPS = (numRows - 1) + (numRows - 1);
    for (int row = 0; row < numRows; row++) {
      for (int i = row; i < N; i += STEPS) {
        out[idx++] = s[i];
        if (row != 0 && row != (numRows - 1)) {
          int nidx = i + (numRows - row - 1) * 2;
          if (nidx < N) {
            // now we are going to add the one going up also.
            out[idx++] = s[nidx];
          }
        }
      }
    }

    return out;
  }
};

int
main()
{
  return 0;
}
