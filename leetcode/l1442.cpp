#include <vector>

class Solution
{
public:
  static constexpr int countTriplets(std::vector<int>& arr)
  {
    const int N = arr.size();
    for (int i = 1; i < N; i++)
      arr[i] ^= arr[i - 1];

    int ans = 0;
    // Edgecase for 0, so we don't need to resize the array.
    for (int k = 1; k < N; k++) {
      if (0 == arr[k])
        ans += k;
    }

    for (int i = 1; i < N - 1; i++) {
      for (int k = i + 1; k < N; k++) {
        if (arr[i - 1] == arr[k])
          ans += k - i;
      }
    }

    return ans;
  }
};
