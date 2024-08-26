#include <array>
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
  static bool stoneGameIX(const std::vector<int>& stones)
  {
    std::array<int, 3> freqs{};
    for (const auto x : stones)
      freqs[x % 3]++;

    // The big insight here, is that the 0 moves only influence is changing the rythem in
    // the game and will have no influence on the outcome of the game, other than to change who
    // makes the last move. Once you realize this, all other moves are forced. The players just
    // play alternativly 2 1 2 1, and the only win condition is that alice is the last one to play
    // a valid move and that when se does so, there are at least one invalid stone on the table.
    constexpr auto aliceWins = [](const int move1, const int move2, const bool hasPause) {
      if (move1 < 0)
        return false;

      const int bal = move1 - move2;
      if (hasPause) {
        return 2 <= bal;
      } else {
        return bal < 0;
      }
    };

    const bool pauseMove = freqs[0] % 2;
    const int N1 = freqs[1];
    const int N2 = freqs[2];

    return aliceWins(N1 - 1, N2, pauseMove) || aliceWins(N2 - 1, N1, pauseMove);
  }
};
