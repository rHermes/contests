/*
 * p1033 - Labyrinth
 *
 * Just use dynamic programming?
 *
 * This is basically a DFS.
 *
 * Thing to note is that we must check both entrances.
 */
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK 0
#define EMPTY 1
#define SEEN 2

// Labyrinth and visited.
// We only need one array. 0 is filled, 1 is empty and 2 is visited.
int8_t L[35][35];
int N;

// Note the order of y and x.
int64_t crawl(int y, int x) {
	// We know that we haven't been here before, so the first thing we do
	// is set this spot to visited.
	L[y][x] = SEEN;
	int64_t ans = 0;


	int8_t tmp1 = L[y][x-1];
	// We check the ones to the left of us and the ones to the right of us.
	if (tmp1 == EMPTY) {
		ans += crawl(y, x-1);
	} else if (tmp1 == BLOCK) {
		ans++;
	}

	tmp1 = L[y][x+1];
	if (tmp1 == EMPTY) {
		ans += crawl(y, x+1);
	} else if (tmp1 == BLOCK) {
		ans++;
	}

	tmp1 = L[y-1][x];
	if (tmp1 == EMPTY) {
		ans += crawl(y-1, x);
	} else if (tmp1 == BLOCK) {
		ans++;
	}

	tmp1 = L[y+1][x];
	if (tmp1 == EMPTY) {
		ans += crawl(y+1, x);
	} else if (tmp1 == BLOCK) {
		ans++;
	}

	return ans;
}

// Buffer.
char buff[35];

int main() {
	fgets(buff, sizeof(buff), stdin);
	
	N = strtol(buff, NULL, 10);
	// Se the corners of the maze to be open.	
	L[0][0] = L[0][1] = L[1][0] = SEEN;
	L[N+1][N+1] = L[N+1][N] = L[N][N+1] = SEEN;

	for (int i = 1; i <= N; i++) {
		fgets(buff, sizeof(buff), stdin);
		for (int j = 1; j <= N; j++) {
			L[i][j] = buff[j-1] != '#';
		}
	}
	
	int64_t ans = crawl(1, 1);
	// Now we just check if the end is seen, and if it isn't we add
	// it's tiles to the equation.
	if (L[N][N] != SEEN) {
		ans += crawl(N, N);
	}

	printf("%" PRId64 "\n", 9*ans);

	return 0;
}
