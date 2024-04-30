#include <iostream>
#include <set>
#include <vector>
#include <cstdint>
#include <utility>

using UT = std::uint64_t;
using ST = std::int64_t;


struct Node {
	UT T{0};
	UT Y{0};
	UT X{0};
};

void advanceIt(std::vector<std::vector<bool>>& grid, UT steps) {
	if (steps == 0)
		return;

	/* auto top = grid[0]; */
	auto top = std::move(grid[0]);

	for (UT j = 0; j < grid.size()-1; j++) {
		grid[j] = grid[j+1];
	}
	grid[grid.size()-1] = top;

	advanceIt(grid, steps-1);
}

void solve() {
	UT N = 0;
	UT M = 0;
	std::cin >> N >> M;

	std::vector<std::vector<bool>> GRID(N);
	for (UT i = 0; i < N; i++) {
		GRID[i].resize(M);
		for (UT j = 0; j < M; j++) {
			UT x = 0;
			std::cin >> x;
			GRID[i][j] = x == 1;
		}
	}

	std::vector<Node> next;
	// These are the places we have been, modulo the time it takes all stones
	// to move back to their start place.
	std::set<std::tuple<UT,UT,UT>> seen;

	next.emplace_back(0, 0, 0);
	while (!next.empty()) {
		std::vector<Node> lsp;

		for (auto& cur : next) {
			auto key = std::make_tuple(cur.T % N, cur.Y, cur.X);
			if (auto it = seen.insert(key); !it.second) {
				continue;
			}

			if (cur.Y == N-1 && cur.X == M-1) {
				std::cout << cur.T << std::endl;
				return;
			}
		

			// Consider going down
			if (GRID[(cur.Y+1) % N][cur.X] == false && GRID[(cur.Y+2)%N][cur.X] == false) {
				lsp.emplace_back(cur.T+1, (cur.Y+1)%N, cur.X);
			}

			// Consider going UP, but we only use this in the last column
			if (cur.X == M-1) {
				lsp.emplace_back(cur.T+1, (cur.Y+N-1) % N, cur.X);
			}


			// Consider going right
			if (cur.X < M-1) {
				if (GRID[(cur.Y+1)%N][cur.X+1] == false) {
					lsp.emplace_back(cur.T+1, cur.Y, cur.X+1);
				}
			}
		}

		next = std::move(lsp);
		advanceIt(GRID, 1);
	}

	std::cout << -1 << std::endl;
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
