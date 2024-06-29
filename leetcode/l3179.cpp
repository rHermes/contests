#include <vector>

class Solution
{
public:
  int valueAfterKSeconds(int n, int k)
  {
    constexpr int MODN = 1000000007;
    std::vector<int> psa(n, 1);
    for (int time = 1; time <= k; time++) {
      for (int i = 1; i < n; i++) {
        psa[i] = (psa[i] + psa[i - 1]) % MODN;
      }
    }

    return psa.back();
  }
};
