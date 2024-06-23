#include <vector>

class Solution
{
public:
  static constexpr int maxSatisfied(const std::vector<int>& customers,
                                    const std::vector<int>& grumpy,
                                    const int minutes)
  {
    // We are really looking for the most amount of unsatifised customers we can fix
    const int N = customers.size();
    int goodAnyways = 0;

    // We just keep a rolling buffer of the last minutes.
    int curBest = 0;

    for (int i = 0; i < minutes; i++) {
      if (grumpy[i]) {
        curBest += customers[i];
      } else {
        goodAnyways += customers[i];
      }
    }

    int maxBest = curBest;
    for (int i = minutes; i < N; i++) {
      if (grumpy[i - minutes]) {
        curBest -= customers[i - minutes];
      }

      if (grumpy[i]) {
        curBest += customers[i];
        maxBest = std::max(maxBest, curBest);
      } else {
        goodAnyways += customers[i];
      }
    }

    return maxBest + goodAnyways;
  }
};
