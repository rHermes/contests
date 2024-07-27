#include <iostream>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static constexpr int maxChunksToSorted(const std::vector<int>& arr)
  {
    const int N = arr.size();
    int ans = 0;
    int watermark = 0;
    for (int i = 0; i < N; i++) {
      const int x = arr[i];
      if (watermark < x)
        watermark = x;

      if (watermark == i)
        ans++;
    }
    return ans;
  }
};
