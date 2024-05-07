#include <iostream>
#include <vector>

class Solution
{
public:
  std::vector<std::vector<int>> findFarmland(std::vector<std::vector<int>>& land)
  {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    auto M = land.size();
    auto N = land[0].size();

    std::vector<std::vector<int>> output;

    for (std::size_t y = 0; y < M; y++) {
      for (std::size_t x = 0; x < N; x++) {
	if (land[y][x] == 0 || (0 < x && land[y][x - 1]) || (0 < y && land[y - 1][x]))
	  continue;

	// ok, now we know we are in the top left. We just keep going
	// down right now.
	const int tx = x;
	const int ty = y;

	int lx = x + 1;
	while (lx < static_cast<int>(N) && land[y][lx])
	  lx++;

	int ly = y + 1;
	while (ly < static_cast<int>(M) && land[ly][x])
	  ly++;

	output.push_back({ ty, tx, ly - 1, lx - 1 });

	x = lx - 1;
      }
    }

    return output;
  }
};

int
main()
{
  return 0;
}
