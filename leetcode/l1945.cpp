#include <array>
#include <string>

class Solution
{
  static constexpr std::array<int, 26> m_lookup = []() {
    std::array<int, 26> out{};
    for (int i = 0; i < 26; i++) {
      int curSum = i + 1;
      while (0 < curSum) {
        out[i] += curSum % 10;
        curSum /= 10;
      }
    }

    return out;
  }();

public:
  static constexpr int getLucky(const std::string& s, const int k)
  {
    int curSum = 0;
    for (const auto c : s) {
      curSum += m_lookup[c - 'a'];
    }

    for (int i = 1; i < k; i++) {
      int nextSum = 0;
      while (0 < curSum) {
        nextSum += curSum % 10;
        curSum /= 10;
      }
      curSum = nextSum;
    }

    return curSum;
  }
};
