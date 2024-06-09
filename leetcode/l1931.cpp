#include <bitset>
#include <cstddef>
#include <vector>

class Solution
{
public:
  int colorTheGrid(int m, int n)
  {
    constexpr int MODM = 1000000007;

    std::vector<std::bitset<15>> valid;
    std::vector<std::pair<std::size_t, std::bitset<15>>> Q;
    Q.emplace_back(1, 1);
    Q.emplace_back(1, 2);
    Q.emplace_back(1, 4);
    while (!Q.empty()) {
      auto [idx, bs] = Q.back();
      Q.pop_back();

      if (idx == static_cast<std::size_t>(m)) {
        valid.push_back(bs);
        continue;
      }

      for (std::size_t i = 0; i < 3; i++) {
        if (!bs[3 * (idx - 1) + i]) {
          bs[3 * idx + i] = true;
          Q.emplace_back(idx + 1, bs);
          bs[3 * idx + i] = false;
        }
      }
    }

    // Ok, now we have the valid bitsets, let's create the db.
    std::vector<std::size_t> prev(valid.size(), 1);
    for (std::size_t row = 1; row < static_cast<std::size_t>(n); row++) {
      std::vector<std::size_t> cur(valid.size());
      // now we go through

      for (std::size_t prevMaskIdx = 0; prevMaskIdx < valid.size(); prevMaskIdx++) {
        const auto prevMask = valid[prevMaskIdx];

        for (std::size_t curMaskIdx = 0; curMaskIdx < valid.size(); curMaskIdx++) {
          const auto curMask = valid[curMaskIdx];
          if ((prevMask & curMask).any())
            continue;

          cur[curMaskIdx] = (cur[curMaskIdx] + prev[prevMaskIdx]) % MODM;
        }
      }

      prev = cur;
    }

    // the sanswer in the end is going to be the sum of all this.

    std::size_t ans = 0;
    for (const auto& ways : prev)
      ans = (ans + ways) % MODM;

    return static_cast<int>(ans);
  }
};
