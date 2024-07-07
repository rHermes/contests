class Solution
{
public:
  static constexpr int numWaterBottles(const int numBottles, const int numExchange)
  {
    int ans = 0;
    int empty = 0;
    int full = numBottles;

    while (0 < full) {
      ans += full;

      empty += full;
      full = empty / numExchange;
      empty %= numExchange;
    }

    return ans;
  }
};
