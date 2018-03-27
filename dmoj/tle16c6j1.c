/*
 * tle16c6j1 - TLE '16 Contest 6 (Mock CCC) J1 - Paper Printing
 *
 * This is a ugly way of doing it, but it works.
 */

#include <stdio.h>

int main() {
	int A, N, M;
	int acts[2*10] = {0};

	scanf("%d %d %d", &N, &M, &A);

	for (int i = 0; i < A; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		acts[2*i] = x;
		acts[2*i+1] = y;
	}

	if (N  > M) {
		printf("The printer jams at 0 second(s).\n");
		return 0;
	}

	// We now have all the actions.
	int *act = acts;
	for (int i = 0; i < 2000+1000; i++) {
		if (N < 0) {
			printf("The printer melts at %d second(s).\n", i);
			break;
		}

		if (*act == i) {
			act++;
			N += *act++;
		}

		if (N > M) {
			printf("The printer jams at %d second(s).\n", i);
			break;
		}

		N--;
	}
	return 0;
}
