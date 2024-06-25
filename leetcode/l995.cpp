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
  static int minKBitFlips(const std::vector<int>& nums, const int k)
  {
    const int N = nums.size();

    std::vector<unsigned char> Q(k, false);
    int Qidx = 0;

    int result = 0;
    bool flipped = 0;

    for (int i = 0; i < N; i++) {
      flipped = (flipped != Q[Qidx]);

      if (flipped == nums[i]) {
        if (N < i + k)
          return -1;

        Q[Qidx++] = true;
        flipped = !flipped;

        result += 1;
      } else {
        Q[Qidx++] = false;
      }

      if (Qidx == k)
        Qidx = 0;
    }

    return result;
  }
};
