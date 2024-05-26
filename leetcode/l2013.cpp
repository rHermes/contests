#include <array>
#include <iostream>
#include <vector>

constexpr int MAXN = 1001;
constexpr int ROW = MAXN + 1;

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class DetectSquares
{
  std::array<int, ROW * ROW> data{};

public:
  void add(const std::vector<int>& point) { data[point[1] * ROW + point[0]]++; }

  int count(const std::vector<int>& point)
  {
    const int tx = point[0];
    const int ty = point[1];

    int ans = 0;

    for (int i = 0; i < MAXN; i++) {
      if (i == tx)
        continue;

      if (data[ty * ROW + i] == 0)
        continue;

      int dist = std::abs(i - tx);

      if (ty + dist < MAXN) {
        ans += (data[ty * ROW + i] * data[(ty + dist) * ROW + i] * data[(ty + dist) * ROW + tx]);
      }

      if (0 <= ty - dist) {
        ans += (data[ty * ROW + i] * data[(ty - dist) * ROW + i] * data[(ty - dist) * ROW + tx]);
      }
    }

    return ans;
  }
};

int
main()
{
  return 0;
}
