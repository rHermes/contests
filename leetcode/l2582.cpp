class Solution
{
public:
  static constexpr int passThePillow(int n, int time)
  {
    const int round = time / (n - 1);
    const int timeIntoRound = time % (n - 1);
    if (round % 2 == 0) {
      return timeIntoRound + 1;
    } else {
      return n - timeIntoRound;
    }
  }
};
