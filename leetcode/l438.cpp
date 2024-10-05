#include <array>
#include <cstdint>
#include <string>
#include <vector>

class Solution
{
public:
  static std::vector<int> findAnagrams(const std::string& s, const std::string& p)
  {
    const int N1 = p.size();
    const int N2 = s.size();
    if (N2 < N1) {
      return {};
    }

    std::array<std::int16_t, 26> seen{};
    for (int i = 0; i < N1; i++) {
      seen[p[i] - 'a']++;
    }

    // I use a sum variable rather tham a count, as it's easier to
    // update, leading to fewer branches.
    int sum = 0;
    for (int i = 0; i < 26; i++) {
      sum += (i + 1) * seen[i];
    }

    std::vector<int> out;

    int l = 0;
    for (int r = 0; r < N2; r++) {
      const auto c = s[r] - 'a';

      seen[c]--;
      sum -= (c + 1);

      while (seen[c] < 0) {
        const auto d = s[l++] - 'a';
        sum += d + 1;
        seen[d]++;
      }

      if (sum == 0) {
        out.push_back(l);
      }
    }

    return out;
  }
};
