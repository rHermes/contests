#include <vector>

class Solution
{
public:
  static constexpr int minSwapsCouples(std::vector<int>& row)
  {
    const int N = row.size();

    constexpr auto ptn = [](const auto idx) { return (idx % 2 == 0) ? (idx + 1) : (idx - 1); };

    std::vector<int> pos(N);
    for (int i = 0; i < N; i++) {
      pos[row[i]] = i;
    }

    // This find the spot next to the partner of idx.
    const auto spotNextToPartner = [&](const int idx) {
      const auto partner = ptn(row[idx]);
      const auto posPartner = pos[partner];
      return ptn(posPartner);
    };

    int ans = 0;
    for (int i = 0; i < N; i += 2) {
      for (int j = spotNextToPartner(i); i != j; j = spotNextToPartner(i)) {
        std::swap(row[i], row[j]);           // Swap their values in the row.
        std::swap(pos[row[i]], pos[row[j]]); // swap the position of their values.
        ans++;
      }
    }

    return ans;
  }
};
