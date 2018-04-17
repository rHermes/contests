/*
 * p1034 - Queens in Peaceful Positions
 *
 * This is a variation of the n queens problem and specificially the
 * n queen completion problem.
 *
 * Remember that it cannot be the exact same position as the one we have.
 * 
 * We can restrict each queen to one row, as there is always going to be one
 * queen per row. When we move 3 queens, this opens up 2 new x locations for
 * each of the 3 queens. Since we need to move all queens, there are then 2
 * new possible arranagements we need to test. Since we know that there are
 * no queens here on the diagonal and horisontal, otherwise the original layout
 * would not have been valid, we need only check the diagonals for collisions.
 *
 * Here is where the trick comes in! Originally I check each level for
 * collisions by checking if |x - moved queen x| == | y - moved queen y| if
 * the two where not 0. This is not fast enough, and I only got a 0.015s for
 * this.
 *
 * Looking at the ever great Otrebus[1], I learned that faster way to do this
 * is to keep track of the number of queens on each diagonal. We find the
 * diagonal of each spot by adding the x and y together, to get the diagonal
 * number.
 *
 * Implementing this I managed to get a 0.001 time and I'm ranked number 13 on
 * this problem.
 *
 * [1] https://github.com/Otrebus/timus/blob/master/1034.cpp
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50

// There is only one queen per y level, so we can encode them as an array.
short queens[MAX_N];
unsigned short UR[MAX_N*2];
unsigned short DL[MAX_N*2];

// To test out a configuration, we simply have to test out if there is any
// diagonal collisions.

unsigned short qadd(const short x, const short y, const short N) {
	return !(UR[x + y]++ | DL[N-x-1 + y]++);
}

void qdel(const short x, const short y, const short N) {
	UR[x + y]--;
	DL[N-x-1 + y]--;
}

char buff[16];
int main() {
	fgets(buff, sizeof(buff), stdin);
	const short N = strtol(buff, NULL, 10);

	for (int i = 0; i < N; i++) {
		char *tmp = fgets(buff, sizeof(buff), stdin);
		int x = strtol(tmp, &tmp, 10);
		int y = strtol(tmp, &tmp, 10);	

		queens[y-1] = x-1;
		qadd(x-1, y-1, N);
	}
	

	unsigned long long ans = 0;
	for (int i = 0; i < N-2; i++) {
		for (int j = i+1; j < N-1; j++) {
			for (int k = j+1; k < N; k++) {
				// Here we try the 2 different variations we can have.
				const short xi = queens[i];
				const short xj = queens[j];
				const short xk = queens[k];

				// Remove normal.
				qdel(xi, i, N);
				qdel(xj, j, N);
				qdel(xk, k, N);

				ans += qadd(xi, j, N) & qadd(xj, k, N) & qadd(xk, i, N);

				// Remove again.
				qdel(xi, j, N);
				qdel(xj, k, N);
				qdel(xk, i, N);

				// Try second.
				ans += qadd(xi, k, N) & qadd(xj, i, N) & qadd(xk, j, N);

				qdel(xi, k, N);
				qdel(xj, i, N);
				qdel(xk, j, N);

				// Restore normal.
				qadd(xi, i, N);
				qadd(xj, j, N);
				qadd(xk, k, N);
			}
		}
	}

	printf("%llu\n", ans);
	return 0;
}
