#include <bitset>
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
  static constexpr int partitionString(const std::string& s)
  {
    // ok, so we can easily figure out what the longest we can keep going.
    const int N = s.size();

    // We don't need the extra bits, 26 is all that is needed, but by doing
    // it this way, the compiler produces better code.
    std::bitset<32> seen;

    int ans = 1;

    // I think we can just be greedy here
    for (int r = 0; r < N; r++) {
      const auto c = s[r] - 'a';
      if (seen[c]) {
        seen.reset();
        ans++;
      }
      seen[c] = true;
    }

    return ans;
  }
};

int
main()
{
  return 0;
}
