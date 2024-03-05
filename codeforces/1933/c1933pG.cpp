#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cinttypes>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <utility>

using UT = std::uint64_t;
using ST = std::int64_t;


constexpr UT MOD_M = 998244353;
/* constexpr UT MOD_M = 998244352; */


struct Node {
	UT T{0};
	UT Y{0};
	UT X{0};

	auto operator<=>(const Node&) const = default;
};

constexpr inline UT IDX(const UT M, const UT y, const UT x) {
	return M*y + x;
}

UT numPossibilites(const UT N, const UT M, std::vector<std::uint8_t>& board, const UT y, const UT x) {
	// First we check if we are indeterminte state.
	if (board[IDX(M, y, x)] == 0) {
		board[IDX(M, y, x)] = 1;
		UT ans = numPossibilites(N, M, board, y, x);

		board[IDX(M, y, x)] = 2;
		ans = (ans + numPossibilites(N, M, board, y, x)) % MOD_M;

		// we return it to the original state.
		board[IDX(M, y, x)] = 0;
		return ans;
	}

	// Up
	if (1 < y 
		&& board[IDX(M, y, x)] == board[IDX(M, y-1, x)] 
		&& board[IDX(M, y, x)] == board[IDX(M, y-2, x)]) {
		/* std::cout << "not alloved" << std::endl; */
		return 0;
	}
	// Up and left
	if (1 < y  && 1 < x
		&& board[IDX(M, y, x)] == board[IDX(M, y-1, x-1)] 
		&& board[IDX(M, y, x)] == board[IDX(M, y-2, x-2)]) {
		return 0;
	}
	// Up and right
	if (1 < y  && x < M-2
		&& board[IDX(M, y, x)] == board[IDX(M, y-1, x+1)] 
		&& board[IDX(M, y, x)] == board[IDX(M, y-2, x+2)]) {
		return 0;
	}
	// Left
	if (1 < x
		&& board[IDX(M, y, x)] == board[IDX(M, y, x-1)]
		&& board[IDX(M, y, x)] == board[IDX(M, y, x-2)]) {
		return 0;
	}

	// we now know we are valid still, so we return the next.
	if (y == N-1 && x == M-1) {
		for (UT j = 0; j < N; j++) {
			for (UT i = 0; i < M; i++) {
				if (board[IDX(M, j, i)] == 1) {
					std::cout << "██";
				} else if (board[IDX(M, j, i)] == 2) {
					std::cout << "  ";
				} else {
					std::cout << "X ";
				}
			}
			std::cout << std::endl;
		}

		std::cout << std::endl;

		return 1;
	} else if (x == M-1) {
		return numPossibilites(N, M, board, y+1, 0);
	} else {
		return numPossibilites(N, M, board, y, x+1);
	}
}


void solve() {
	UT N = 0;
	UT M = 0;
	UT Q = 0;
	std::cin >> N >> M >> Q;

	std::vector<std::uint8_t> board(N*M);
	board[0] = 1;

	UT ans1 = numPossibilites(N, M, board, 0, 0);
	std::cout << ans1 << std::endl;
	for (UT q = 0; q < Q; q++) {
		UT r = 0;
		UT c = 0;
		std::string shape;
		std::cin >> r >> c >> shape;

		if (shape == "circle")
			board[IDX(M, r-1, c-1)] = 1;
		else
			board[IDX(M, r-1, c-1)] = 2;
		
		/* ans1 = numPossibilites(N, M, board, 0, 0); */
		/* std::cout << ans1 << std::endl; */
		/* std::cout << "R=" << r << " C=" << c << " shape=[" << shape << "]" << std::endl; */
	}
}

int main() {
	std::cin.tie(0);
	std::cin.sync_with_stdio(false);

	UT T = 0;
	std::cin >> T;

	for (UT t = 0; t < T; t++) {
		solve();
	}
}
