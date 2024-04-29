#include <bitset>
#include <iostream>
#include <vector>

static auto _ = []() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	return nullptr;
}();

class Solution {
public:
	using CharBoard = std::vector<std::vector<char>>;

	static bool solve(CharBoard& board, int y = 0) {
		for (; y < 9; y++) {
			for (int x = 0; x < 9; x++) {
				if (board[y][x] != '.')
					continue;

				// we must see if there is any way to put anything here.
				std::bitset<10> pos;
				pos.set();
				pos.reset(0);

				// we check the row.
				for (int rowX = 0; rowX < 9; rowX++) {
					if (board[y][rowX] != '.') {
						pos.reset(board[y][rowX] - '0');
					}
				}

				for (int rowY = 0; rowY < 9; rowY++) {
					if (board[rowY][x] != '.') {
						pos.reset(board[rowY][x] - '0');
					}
				}

				// ok, now let's find the quandrant.
				const int groupY = y / 3;
				const int groupX = x / 3;

				for (int rowY = groupY * 3; rowY < (groupY + 1) * 3; rowY++) {
					for (int rowX = groupX * 3; rowX < (groupX + 1) * 3;
					rowX++) {
						if (board[rowY][rowX] != '.') {
							pos.reset(board[rowY][rowX] - '0');
						}
					}
				}

				// ok, so if there is zero way to do this, we return 0.
				if (pos.none()) {
					return false;
				}

				// now we try each one.
				for (int i = 1; i < 10; i++) {
					if (!pos[i])
						continue;

					board[y][x] = '0' + i;
					if (solve(board, y))
						return true;
				}

				board[y][x] = '.';
				return false;
			}
		}

		return true;
	}

	static void solveSudoku(CharBoard& outBoard) {
		if (!solve(outBoard)) {
			throw std::runtime_error("Every question should be solvable");
		}
	}
};

int main() { return 0; }
