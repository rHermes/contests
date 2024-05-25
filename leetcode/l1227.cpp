class Solution
{
public:
  constexpr static double nthPersonGetsNthSeat(int n)
  {
    if (n == 1) {
      return 1;
    } else {
      return 0.5;
    }
  }
};

int
main()
{
  return 0;
}
