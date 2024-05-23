// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

int
rand7()
{
  return 0;
}

class Solution
{
public:
  static int rand10()
  {
    while (true) {
      // this will be a number between 0 and 48.
      unsigned int dice = 7 * (rand7() - 1) + rand7() - 1;

      if (dice < 40) {
        // the back digits are repeated 4 times here, so they have
        // and equal oppertunity.
        return 1 + (dice % 10);
      }
    }
  }
};

int
main()
{
  return 0;
}
