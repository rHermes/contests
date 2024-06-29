class Solution
{
public:
  static constexpr int poorPigs(int buckets, int minutesToDie, int minutesToTest)
  {
    int rounds = minutesToTest / minutesToDie;

    int res = 1;
    int ans = 0;
    while (res < buckets) {
      res *= rounds + 1;
      ans++;
    }

    return ans;
  }
};
