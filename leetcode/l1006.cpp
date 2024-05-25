class Solution
{
public:
  static int clumsy(int n)
  {
    char i = 0;
    int left = n;
    n--;

    int total = 0;

    while (0 < n) {
      switch (i) {
        case 0:
          left *= n;
          break;

        case 1:
          left /= n;
          break;

        case 2:
          total += left + n;
          left = 0;
          break;

        case 3:
          total += left;
          left = -n;
          i = -1;
          break;
      }

      i++;
      n--;
    }

    return total += left;
  }
};

int
main()
{
  return 0;
}
