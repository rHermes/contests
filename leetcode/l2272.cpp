#include <array>
#include <string>
#include <cstdint>

class Solution {
public:
  int largestVariance(const std::string &s) {

    // Ok, we are creating a info struct.
    struct Info {
      std::int16_t major{0};
      std::int16_t minor{0};
      bool flag{false};
    };

    // Making a wrapped array.
    std::array<std::array<Info, 26>, 26> DP{};

    int ans = 0;
    for (const auto letter : s) {
      const int c = letter - 'a';

      // Update all infos where c is a minor.
      for (int i = 0; auto &info : DP) {
        if (c == i++)
          continue;

        // ok, so we are using the C as the major now.
        auto &[major, minor, flag] = info[c];

        // Flag here indicate that we come from a negative state.
        if (flag) {
          minor--;
          flag = false;
        }

        minor++;
        if (major < minor) {
          major = 0;
          minor = 1;
          flag = true;
        } else {
          ans = std::max(ans, major - minor);
        }
      }

      // Update C info, where c is the major
      for (int i = 0; auto &[major, minor, flag] : DP[c]) {
        if (c == i++)
          continue;

        major++;
        if (minor != 0) {
          ans = std::max(ans, major - minor);
        }
      }
    }

    return ans;
  }
};

int main() { return 0; }
