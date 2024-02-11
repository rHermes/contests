#include <cstdio>
#include <cstdint>
#include <set>
#include <unordered_set>
#include <vector>
#include <stdexcept>

/* using ST = std::int64_t; */
using UT = std::uint32_t;


bool play_super_simple_game() {
	printf("2\n");
	fflush(stdout);
	
	bool myTurn = false;
	UT lastR = 0;
	UT lastC = 0;
	char lel = 'a';
	while (1) {
		if (myTurn) {
			if (lastR == 1 && lastC == 1)
				printf("1 2\n");
			else
				printf("1 1\n");

			fflush(stdout);
			while (true) {
				lel = getc(stdin);
				if (!isspace(lel))
					break;
			}

			if (lel == 'L' || lel == 'I') {
				return true;
			}
			else if (lel == 'W') {
				return false;
			}
		} else {
			scanf("%u %u", &lastR, &lastC);
			while (true) {
				lel = getc(stdin);
				if (!isspace(lel))
					break;
			}

			if (lel == 'L' || lel == 'I') {
				return true;
			}
			else if (lel == 'W') {
				return false;
			}
		}

		myTurn = !myTurn;
	}

	return false;
}

bool play_defensive_game(const UT N, const UT M) {
	printf("2\n");
	fflush(stdout);
	
	bool myTurn = false;
	UT lastR = 0;
	UT lastC = 0;
	std::vector<std::vector<bool>> rows;
	for (UT l = 0; l < N; l++) {
		std::vector<bool> row(M);
		rows.push_back(row);
	}
	char lel = 'a';

	while (1) {
		if (myTurn) {
			UT active = 0;
			for (const auto& row : rows)  {
				for (const auto& v : row) {
					if (v)
						active++;
				}
			}

			// HE removed his own piece
			if (!rows[lastR-1][lastC-1]) {
				// We will now remove our only piece.
				UT pickRow = (lastR == 1) ? 1 : 0;
				UT goodCol = 0;
				for (goodCol = 0; goodCol < M; goodCol++) {
					if (rows[pickRow][goodCol]) {
						rows[pickRow][goodCol] = false;
						printf("%u %u\n", pickRow+1, goodCol+1);
						break;
					}
				}
				if (goodCol == M)
					throw std::runtime_error("Something messed up in him returning his own piece\n");
			}
			else if (active == 1) {
				// He just placed the first piece. Aka there is only 1 on the table.
				UT pickRow = (lastR == 1) ? 1 : 0;
				rows[pickRow][0] = true;
				printf("%u 1\n", pickRow+1);
			} else {
				// He played a new spot. We always remove the other item in that row
				UT pickRow = lastR-1;
				UT goodCol = 0;
				for (goodCol = 0; goodCol < M; goodCol++) {
					if (goodCol == lastC-1)
						continue;

					if (rows[pickRow][goodCol]) {
						rows[pickRow][goodCol] = false;
						printf("%u %u\n", pickRow+1, goodCol+1);
						break;
					}
				}
			}

			fflush(stdout);
			while (true) {
				lel = getc(stdin);
				if (!isspace(lel))
					break;
			}

			if (lel == 'L' || lel == 'I') {
				return true;
			}
			else if (lel == 'W') {
				return false;
			}
		} else {
			scanf("%u %u", &lastR, &lastC);
			while (true) {
				lel = getc(stdin);
				if (!isspace(lel))
					break;
			}
			rows[lastR-1][lastC-1] = !rows[lastR-1][lastC-1];

			if (lel == 'L' || lel == 'I') {
				return true;
			}
			else if (lel == 'W') {
				return false;
			}
		}

		myTurn = !myTurn;
	}
	return false;
}

bool play_off_single(const UT M) {
	bool myTurn = false;
	UT lastR = 0;
	UT lastC = 0;
	char lel = 'a';
	std::vector<bool> row(M);
	
	
	// We always start and we put it in the middle row
	printf("1\n");
	printf("1 %u\n", ((M-1)/2)+1);
	row[((M-1)/2)] = true;
	fflush(stdout);
	while (true) {
		lel = getc(stdin);
		if (!isspace(lel))
			break;
	}

	if (lel == 'L' || lel == 'I') {
		return true;
	}
	else if (lel == 'W') {
		return false;
	}

	while (1) {
		if (myTurn) {
			// We always progress with our current binary search.
			std::vector<UT> pos;
			for (UT col = 0; col < M; col++) {
				if (row[col])
					pos.push_back(col);
			}

			if (pos.size() < 2) {
				throw std::domain_error("WTF");
			}

			// we now find the diff
			UT minDiff = 100000000;
			UT left = 0;
			UT right = 0;

			for (UT i = 0; i < pos.size()-1; i++) {
				UT diff = pos[i+1] - pos[i];
				if (diff < minDiff) {
					minDiff = diff;
					left = pos[i];
					right = pos[i+1];
				}
			}

			// we have two next to each other, we just need to figure out if we are on the edge or not.
			if (left+1 == right) {
				if (right == M-1) {
					printf("1 %u\n", left-1+1);
					row[left-1] = true;
				} else {
					printf("1 %u\n", right+1+1);
					row[right+1] = true;
				}
			} else {
				// They are not right next to each other, and there is no spots between them
				UT mid = (right+left)/2;
				row[mid] = true;
				printf("1 %u\n", mid+1);
			}


			fflush(stdout);
			while (true) {
				lel = getc(stdin);
				if (!isspace(lel))
					break;
			}

			if (lel == 'L' || lel == 'I') {
				return true;
			}
			else if (lel == 'W') {
				return false;
			}
		} else {
			scanf("%u %u", &lastR, &lastC);
			row[lastC-1] = !row[lastC-1];
			while (true) {
				lel = getc(stdin);
				if (!isspace(lel))
					break;
			}

			if (lel == 'L' || lel == 'I') {
				return true;
			}
			else if (lel == 'W') {
				return false;
			}
		}

		myTurn = !myTurn;
	}
	return false;
}

bool play_off_full(const UT N, const UT M) {
	bool myTurn = true;
	UT lastR = 0;
	UT lastC = 0;
	char lel = 'a';
	std::vector<std::vector<bool>> rows;
	for (UT i = 0; i < N; i++) {
		std::vector<bool> row(M);
		rows.push_back(row);
	}

	
	// We always start and we put it in the middle row
	printf("1\n");

	UT midY = (N-1)/2;
	UT midX = (M-1)/2;
	printf("%u %u\n", midY+1, midX+1);
	rows[midY][midX] = true;
	fflush(stdout);
	while (true) {
		lel = getc(stdin);
		if (!isspace(lel))
			break;
	}

	if (lel == 'L' || lel == 'I') {
		return true;
	}
	else if (lel == 'W') {
		return false;
	}

	// What the machine does
	scanf("%u %u", &lastR, &lastC);
	rows[lastR-1][lastC-1] = true;
	/* row[lastC-1] = !row[lastC-1]; */
	while (true) {
		lel = getc(stdin);
		if (!isspace(lel))
			break;
	}

	UT machineFirstR = lastR;
	UT machineFirstC = lastC;

	if (lel == 'L' || lel == 'I') {
		return true;
	}
	else if (lel == 'W') {
		return false;
	}

	bool doingVert = false;
	UT constRow = 0;
	UT constCol = 0;

	// Now, either he placed it in the row, which we then go vertical.
	if (lastC-1 == midX) {
		doingVert = true;
		constCol = midX;

	} else if (lastR-1 == midY) {
		doingVert = false;
		constRow = midY;
		// We are skipping straight to a search here then
	} else {
		printf("%u %u\n", lastR, midX+1);
		rows[lastR-1][midX] = true;
		fflush(stdout);
		while (true) {
			lel = getc(stdin);
			if (!isspace(lel))
				break;
		}

		if (lel == 'L' || lel == 'I') {
			return true;
		}
		else if (lel == 'W') {
			return false;
		}

		UT oldLastR = lastR;
		/* UT oldLastC = lastC; */


		// What the machine does
		scanf("%u %u", &lastR, &lastC);
		rows[lastR-1][lastC-1] = !rows[lastR-1][lastC-1];
		/* row[lastC-1] = !row[lastC-1]; */
		while (true) {
			lel = getc(stdin);
			if (!isspace(lel))
				break;
		}
		if (lel == 'L' || lel == 'I') {
			return true;
		}
		else if (lel == 'W') {
			return false;
		}
	
		// either it picked the last
		if (lastR-1 == midY && lastC-1 == midX) {
			// We are doing horizontal
			doingVert = false;
			constRow = oldLastR-1;
		} else if (lastR == machineFirstR && lastC == machineFirstC) {
			// it picked it's own first, this means we are doing vert
			doingVert = true;
			constCol = midX;
		} else {
			// it picked something else, which is stupid, but it allows us to start doing vert, as it's the fastest
			doingVert = true;
			constCol = midX;
		}
	}

	while (1) {
		if (myTurn) {
			if (doingVert) {
				// We always progress with our current binary search.
				std::vector<UT> pos;
				for (UT row = 0; row < N; row++) {
					if (rows[row][constCol])
						pos.push_back(row);
				}

				if (pos.size() < 2) {
					throw std::out_of_range("WTF");
				}

				// we now find the diff
				UT minDiff = 100000000;
				UT left = 0;
				UT right = 0;

				for (UT i = 0; i < pos.size()-1; i++) {
					UT diff = pos[i+1] - pos[i];
					if (diff < minDiff) {
						minDiff = diff;
						left = pos[i];
						right = pos[i+1];
					}
				}

				// we have two next to each other, we just need to figure out if we are on the edge or not.
				if (left+1 == right) {
					if (right == N-1) {
						printf("%u %u\n", left-1+1, constCol+1);
						rows[left-1][constCol] = true;
					} else {
						printf("%u %u\n", right+1+1, constCol+1);
						rows[right+1][constCol] = true;
					}
				} else {
					// They are not right next to each other, and there is no spots between them
					UT mid = (right+left)/2;
					rows[mid][constCol] = true;
					printf("%u %u\n",mid+1, constCol+1);
				}
			} else {
				// We always progress with our current binary search.
				std::vector<UT> pos;
				for (UT col = 0; col < M; col++) {
					if (rows[constRow][col])
						pos.push_back(col);
				}

				if (pos.size() < 2) {
					throw std::bad_alloc(); // ("WTF");
				}

				// we now find the diff
				UT minDiff = 100000000;
				UT left = 0;
				UT right = 0;

				for (UT i = 0; i < pos.size()-1; i++) {
					UT diff = pos[i+1] - pos[i];
					if (diff < minDiff) {
						minDiff = diff;
						left = pos[i];
						right = pos[i+1];
					}
				}

				// we have two next to each other, we just need to figure out if we are on the edge or not.
				if (left+1 == right) {
					if (right == M-1) {
						printf("%u %u\n", constRow+1, left-1+1);
						rows[constRow][left-1] = true;
					} else {
						printf("%u %u\n", constRow+1, right+1+1);
						rows[constRow][right+1] = true;
					}
				} else {
					// They are not right next to each other, and there is no spots between them
					UT mid = (right+left)/2;
					rows[constRow][mid] = true;
					printf("%u %u\n", constRow+1, mid+1);
				}
			}


			fflush(stdout);
			while (true) {
				lel = getc(stdin);
				if (!isspace(lel))
					break;
			}

			if (lel == 'L' || lel == 'I') {
				return true;
			}
			else if (lel == 'W') {
				return false;
			}
		} else {
			scanf("%u %u", &lastR, &lastC);
			rows[lastR-1][lastC-1] = !rows[lastR-1][lastC-1];
			while (true) {
				lel = getc(stdin);
				if (!isspace(lel))
					break;
			}

			if (lel == 'L' || lel == 'I') {
				return true;
			}
			else if (lel == 'W') {
				return false;
			}
		}

		myTurn = !myTurn;
	}
	return false;
}

int main() {
	UT N = 0;
	UT M = 0;
	UT T = 0;
	scanf("%u %u %u", &N, &M, &T);

	// I will remove some common ones as it's easier then.
	for (int i = 0; i < T; i++) {
		if (M == 2) {
			bool term = play_super_simple_game();
			if (term)
				return 0;
		} else if (N == 2) {
			bool term = play_defensive_game(N, M);
			if (term)
				return 0;
		} else if (N == 1) {
			bool term = play_off_single(M);
			if (term)
				return 0;
		} else {
			// This is standard offensive 
			bool term = play_off_full(N, M);
			if (term)
				return 0;
		}
	}
	
	return 0;
}
