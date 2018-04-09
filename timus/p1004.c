/*
 * p1004 - Sightseeing Trip
 *
 * This is taken from the official solution, since my own attempt with dijekstra
 * was to slow, I'm trying to understand the official solution.
 *
 * This seems to be a modified version of floyds algorithm.
 *
 * This might be an edge disjoint problem?
 */

#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100
#define INF 4000000L


uint32_t (*d)[MAXN], (*q)[MAXN];

/*
void print_q(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%10" PRIu32 " ", q[i][j]);
		}
		printf("\n");
	}
}
void print_d(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%10" PRIu32 " ", d[i][j]);
		}
		printf("\n");
	}
}

*/
int main() {

	// First we alloc the arrays.
	d = malloc(sizeof(uint32_t) * MAXN * MAXN);
	q = malloc(sizeof(uint32_t) * MAXN * MAXN);
	if (!d || !q) {
		return 1;
	}

	// We scan in n and m;
	while (1) {
		// Variables.
		int n, m;
		/*
		int i, j, k;
		*/
		uint16_t x, y;
		uint32_t z, z0;

		z0 = z0;

		int rc = scanf("%d %d", &n, &m);
		if (rc != 2) {
			break;
		}

		// We set both arrays to infinity.
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				d[i][j] = INF;
				q[i][j] = INF;
			}
		}

		// We scan for the lines.
		for (int i = 0; i < m; i++) {
			scanf("%" SCNu16 " %" SCNu16 " %" SCNu32, &x, &y, &z);
			x--;
			y--;

			// We set the distance on both to the smallest it can be.
			if (d[x][y] > z && x != y) {
				d[x][y] = z;
				d[y][x] = z;
			}
		}

		// we are now done with the input.
		// printf("Done reading input!\n");
		
		z = INF;
		x = 0;
		y = 0;
		z0 = INF;



		for (int i = 0; i < n; i++) {
			/*
			printf("\n\nBEFORE %d:\n", i);
			print_q(n);

			printf("D:\n");
			print_d(n);
			*/

			// we set the q to 0
			q[i][i] = 0;

			// This means the distance from 
			
			// I think this is finding the smallest z?
			//
			
			// Think I understand this one. For each node,
			// we check the distance from j to k and from
			// i to k and i to j. 
			//
			// So here we find the smallest possible route with loops.
			for (int j = 0; j < i; j++) {
				for (int k = 0; k < i; k++) {
					if (j != k) {
						// so the distance from i to k and i to j
						z0 = q[j][k] + d[i][k] + d[i][j];
						if (z0 < z) {
					//		printf("Setting z: %d %d %d\n", i, j, k);
							z = z0;
							x = i;
							y = j;
						}
					}
				}
			}

			// printf("z: %" PRIu32 "\n", z);
			
			// here we check the fastest way to go to
			// j from i, without going directly.
			// so we go through q[i][k] and see if we have 
			// a way from j to k and a direct jump from k to i.
			//
			// We are basically here checking all nodes less than
			// i, if there is a way to reach a neighboor of i that
			// is less than it.
			for (int j = 0; j < i; j++) {
				// the distance from i to j is infinite.
				// NOTE, this does not go for the distance
				// from j to i.
				q[i][j] = INF;

				for (int k = 0; k < i; k++) {
					// so if the q distance from i to j
					if (q[i][j] > q[j][k] + d[k][i]) {
						q[i][j] = q[j][k] + d[k][i];
					}
				}

				// Now we mirror it.
				q[j][i] = q[i][j];
			}


			// Last thing.
			// This is like normal floyd marshal, but we
			// are finding the shortest way to go
			// from j to k, via i.
			for (int j = 0; j < i; j++) {
				for (int k = 0; k < i; k++) {
					if (q[j][k] > q[j][i] + q[i][k]) {
						q[j][k] = q[j][i] + q[i][k];
					}
				}
			}
			/*
			printf("AFTER: \n");
			print_q(n);
			*/
		}
		// What we really have after this is x y z. z is the 
		// distance and x and y are the two nodes.

		if (z == INF) {
			printf("No solution.\n");
			continue;
		}

		// Now we simply set path between these two too INF.
		d[x][y] = INF;
		d[y][x] = INF;

		// Now we do a normal floyd marshal, to find the shortest path from y to x.
		memcpy(q, d, sizeof(uint32_t) * MAXN * MAXN);
		for (int i = 0; i < n; i++) {
			q[i][i] = 0;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					if (q[j][k] > q[j][i] + q[i][k]) {
						q[j][k] = q[j][i] + q[i][k];
					}
				}
			}
		}

		while (x != y) {
			printf("%" PRIu16 " ", y + 1);
			for (int i = 0; i < n; i++) {
				if (q[y][x] == q[i][x] + d[y][i]) {
					y = i;
					break;
				}
			}
		}
		printf("%" PRIu32 "\n", x + 1);
	}

	

	
	// We free the arrays, because we are gentlemen.
	free(d);
	free(q);
	return 0;
}
