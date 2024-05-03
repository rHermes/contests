#include <string>
#include <array>

class Solution {
public:
  int largestVariance(const std::string& s) {
    std::array<int, 26> counts{};
    for (const auto c : s)
      counts[c - 'a']++;

    int ans = 0;
    // ok, now we repeat Kadanes algortihm caross.
    for (int i = 0; i < 26; i++) {
      for (int j = 0; j < 26; j++) {
        if (i == j || !counts[i] || !counts[j])
          continue;

        // ok, so we have a major and minor one at this point. Let's
        // think a bit.

        int MajorLeft = counts[i];
        int MinorLeft = counts[j];

        int major_count = 0;
        int minor_count = 0;
        for (const auto cc : s) {
          const int c = cc - 'a';

          if (c == i) {
            major_count++;

            if (0 < minor_count)
              ans = std::max(major_count - minor_count, ans);

            MajorLeft--;
            if (MajorLeft == 0) {
              if (minor_count == 0)
                ans = std::max(major_count - 1, ans);

              break;
            }
          } else if (c == j) {
            minor_count++;

            if (minor_count == 1)
              ans = std::max(major_count - minor_count, ans);

            MinorLeft--;
            if (MinorLeft == 0) {
              ans = std::max(ans, major_count - minor_count + MajorLeft);
              break;
            }

            if (major_count < minor_count) {
              minor_count = 0;
              major_count = 0;
            }
          }
        }
      }
    }
    return ans;
  }
};

int main() { return 0; }
