#include <bitset>
#include <cinttypes>
#include <iostream>
#include <string>
#include <vector>

using UT = std::uint64_t;

constexpr UT N = 7;
struct Board {
	std::bitset<N*N> board;

	void set(UT y, UT x, bool value) {
		board.set(y*N + x, value);
	}

	bool get(UT y, UT x) {
		return board.test(y*N + x);
	}

	[[nodiscard]] bool test(UT y, UT x) {
		// This can be made faster, I know it, but I have to look into this.
		// We can build some sort of 
		if (y < 1 || 5 < y || x < 1 || 5 < x)
			return false;

		return get(y,x) && get(y-1,x-1) && get(y-1,x+1) && get(y+1,x-1) && get(y+1,x+1);
	}
};

void solveDFS(Board& board, const bool even, UT& bestAns, const UT y, const UT x, const UT movesMade) {
	// we quit early, no need to wait around
	if (bestAns <= movesMade) {
		return;
	}

	// We are finished here.
	if (y == 6) {
		bestAns = movesMade;
	} else if (x == 6) {
		// Wrap around for lines.
		solveDFS(board, even, bestAns, y+1, 1, movesMade);
	} else if ((x+y) % 2 == even || !board.test(y, x)) {
		// We skip fields not on our board parity or we don't have a fit here.
		solveDFS(board, even, bestAns, y, x+1, movesMade);
	} else {
		// We now know we have a hit, and we need to do something.
		board.set(y, x, false);
		solveDFS(board, even, bestAns, y, x+1, movesMade+1);
		board.set(y, x, true);

		board.set(y+1, x+1, false);
		solveDFS(board, even, bestAns, y, x+1, movesMade+1);
		board.set(y+1, x+1, true);

		board.set(y+1, x-1, false);
		solveDFS(board, even, bestAns, y, x+1, movesMade+1);
		board.set(y+1, x-1, true);
	}
}

void solve() {
	Board board;
	for (UT i = 0; i < N; i++) {
		std::string wow;
		std::getline(std::cin >> std::ws, wow);

		for (UT j = 0; j < N; j++)
			if (wow[j] == 'B')
				board.set(i, j, true);
	}

	// Found the constants by running algo on an all black board.
	UT oddAns = 8;
	UT evenAns = 8;
	solveDFS(board, false, oddAns, 1, 1, 0);
	solveDFS(board, true, evenAns, 1, 1, 0);

	std::cout << evenAns + oddAns << std::endl;
}

int main() {
	std::cin.tie(0);
	std::cin.sync_with_stdio(false);
	std::cin.exceptions(std::cin.badbit);

	UT T = 0;
	std::cin >> T;
	for (UT t = 0; t < T; t++)
		solve();

	return 0;
}
