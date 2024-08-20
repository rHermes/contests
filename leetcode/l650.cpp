#include <deque>
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
  static int minSteps(const int N)
  {
    if (N == 1)
      return 0;

    const int ROW = N + 1;

    std::vector<unsigned char> seen(ROW * ROW, false);

    std::deque<std::pair<int, int>> Q;
    Q.emplace_back(1, 0);

    seen[1 * ROW + 0] = true;

    int wave = 0;
    while (!Q.empty()) {
      const int numThisWave = Q.size();

      for (int z = 0; z < numThisWave; z++) {
        const auto [curX, curM] = Q.front();
        Q.pop_front();

        if (curX == N) {
          return wave;
        }

        if (N < (curX + curM))
          continue;

        if (curX != curM && !seen[curX * ROW + curX]) {
          seen[curX * ROW + curX] = true;
          Q.emplace_back(curX, curX);
        }

        // it used beunseen
        if (!seen[(curX + curM) * ROW + curM]) {
          seen[(curX + curM) * ROW + curM] = true;
          Q.emplace_back(curX + curM, curM);
        }
      }

      wave++;
    }

    return -1;
  }
};
