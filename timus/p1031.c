/*
 * p1031 - Railway Tickets
 *
 * We always go forward, since it will never pay off to jump past a station and
 * then back.
 *
 * This could be sped up by doing a binary search at the beginning, building up
 * the ranges, for L1, L2 and L3. this would take O(n*log(n)) time.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

#define INF 1000000001

#define min(x,y) ( \
    { __auto_type __x = (x); __auto_type __y = (y); \
      __x < __y ? __x : __y; })


static long L1, L2, L3, C1, C2, C3;
static int END;

char buff[256];
long dist[MAX_N];
long memo[MAX_N] = {0};

// Could also maybe optimize, in that we only ever go the furthes we can 
// with each ticket price? There is no point in going shorter as	
long F(int start) {
	if (start == END) {
		return 0;
	}

	if (memo[start] != 0) {
		return memo[start]-1;
	}

	long base = dist[start];
	long answer = INF;

	// We could optimize this, by only considering one station per length.
	for (int i = start+1; i <= END; i++) {
		long gap = dist[i] - base;

		if (gap <= L1 ) {
			answer = min(answer, C1 + F(i));
		} else if (gap <= L2) {
			answer = min(answer, C2 + F(i));
		} else if (gap <= L3) {
			answer = min(answer, C3 + F(i));
		} else {
			break;
		}
	}

	memo[start] = answer + 1;
	return answer;
}

int main() {
	char *tmp = fgets(buff, sizeof(buff), stdin);

	// Read in the constants.
	L1 = strtol(tmp, &tmp, 10);
	L2 = strtol(tmp, &tmp, 10);
	L3 = strtol(tmp, &tmp, 10);
	C1 = strtol(tmp, &tmp, 10);
	C2 = strtol(tmp, &tmp, 10);
	C3 = strtol(tmp, &tmp, 10);

	// Read in the amount of stations.
	tmp = fgets(buff, sizeof(buff), stdin);
	int N = strtol(tmp, NULL, 10);
	
	// Reasd the goal and the target.
	tmp = fgets(buff, sizeof(buff), stdin);
	int A = strtol(tmp, &tmp, 10);
	int B = strtol(tmp, &tmp, 10);
	
	// If A is bigger than B, we swap.
	if (A > B) {
		int tmp = A;
		A = B;
		B = tmp;
	}


	// Now read in the distances to the first station.
	dist[0] = 0;
	for (int i = 1; i < N; i++) {
		fgets(buff, sizeof(buff), stdin);
		dist[i] = strtol(buff, NULL, 10); 
	}

	// We can build the L1, L2 and L3 here.

	END = B-1;
	long ans = F(A-1);

	printf("%li\n", ans);
	return 0;
}
