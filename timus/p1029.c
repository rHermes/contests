/*
 * p1029 - Ministry
 *
 * The easy way to solve this is to use dijkstras, with two virtual nodes at
 * the top and bottom, with zero weigthed edges to the top and bottom rooms,
 * but there is also a dynamic way of doing it.
 *
 * I initialy solved it with dijkstras, but then after looing at this, I 
 * realized that 
 *
 * https://github.com/ajmarin/coding/blob/master/timus/T1029.cpp
 */

#include <stdio.h>
#include <inttypes.h>

// These defines the scope of the building.
#define M 100
#define N 500

// These are for the io things.
#define TT uint_fast32_t
//#define TT_MAX UINT_FAST32_MAX
#define TT_MAX 1000000002
#define TS SCNuFAST32
#define TP PRIuFAST32

// Global arrays.
TT room[M][N], cost[M][N];

// The logic here, is that we will never go left or right 
uint16_t path[M*N];

#define min(x,y) ( \
    { __auto_type __x = (x); __auto_type __y = (y); \
      __x < __y ? __x : __y; })

int main() {
	int m, n;
	scanf("%d %d", &m, &n);
	
	// Setup loop.
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%" TS, &room[i][j]);
			// Consider using memset at the top level to do this?
			cost[i][j] = TT_MAX;
		}
	}

	// Edge case, if N is 0, we just output 1 M times.
	if (n == 1) {
		printf("1");
		for (int i = 1; i < m; i++) {
			printf(" 1");
		}
		printf("\n");
		return 0;
	}
	
	// Set the base case for the algorithm.
	for (int j = 0; j < N; j++) {
		cost[0][j] = room[0][j];
	}

	// Now we build up the cost array.
	for (int i = 1; i < m; i++) {
		// We check best bath of below, left or right
		for (int j = 0; j < n; j++) {
			cost[i][j] = cost[i-1][j] + room[i][j];
		}
		
		// Left
		for (int j = 1; j < n; j++) {
			cost[i][j] = min(cost[i][j], cost[i][j-1] + room[i][j]);
		}
		
		// Right
		for (int j = n-2; j >= 0; j--) {
			cost[i][j] = min(cost[i][j], cost[i][j+1] + room[i][j]);
		}
	}


	// Now that we have the array built up, we find the best way.
	TT min_cost = TT_MAX;
	int x = 0;
	int y = 0;
	int ps = 0;

	for (int j = 0; j < n; j++) {
		if (cost[m-1][j] < min_cost) {
			x = j;
			min_cost = cost[m-1][j];
		}
	}

	y = m-1;
	while (1) {
		path[ps++] = x+1;
		// Use these for the checks of where to go next.
		TT w = cost[y][x] - room[y][x];
		if (y && w == cost[y-1][x]) {
			y--;
		} else if (x && w == cost[y][x-1]) {
			x--;
		} else if (x < n-1 && w == cost[y][x+1]) {
			x++;
		} else {
			break;
		}
	}

	printf("%" PRIu16, path[--ps]);
	// Print out the path.
	while (ps--) {
		printf(" %" PRIu16, path[ps]);
	}

	printf("\n");

	return 0;
}
