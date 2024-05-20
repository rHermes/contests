#include <limits>
#include <vector>

struct MinLess
{
  int a{ std::numeric_limits<int>::max() };
  int b{ std::numeric_limits<int>::max() };
  std::size_t ai{ 0 };

  void push(std::size_t i, int c)
  {
    if (c < a) {
      b = a;

      a = c;
      ai = i;
    } else if (c < b) {
      b = c;
    }
  }
};

class Solution
{
public:
  int minFallingPathSum(const std::vector<std::vector<int>>& grid)
  {
    const auto N = grid.size();

    MinLess prevMin;
    for (std::size_t i = 0; i < N; i++) {
      prevMin.push(i, grid[0][i]);
    }

    for (std::size_t i = 1; i < N; i++) {
      MinLess curMin;
      auto& row = grid[i];

      for (std::size_t col = 0; col < N; col++) {
        if (col == prevMin.ai)
          curMin.push(col, row[col] + prevMin.b);
        else
          curMin.push(col, row[col] + prevMin.a);
      }

      prevMin = std::move(curMin);
    }

    return prevMin.a;
  }
};

int
main()
{
  return 0;
}
