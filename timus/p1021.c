/*
 * p1021 - Sacrament of the Sum
 *
 * The two lists are already sorted.
 *
 * We read in the first one and for each number in the second list, we
 * check if 10 000 - (num) is in the right list.
 *
 * The other way to do this is to keep a bool array of all the bools
 * and keep that.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/* Way with O(N), but more memory. */
int main() {
	// This is enough to house every number between
	// -32768 and 32767
	bool have[65536];
	memset(have,false,sizeof(have));

	int N;
	scanf("%d", &N);

	int x;
	for (int i = 0; i < N; i++) {
		scanf("%d", &x);

		// We scan in the number and then offset it 
		// by the most negative value, so that it is mappend on
		// onto the range we need.
		have[x+32768] = true;
	}

	scanf("%d", &N);

	bool found = false;
	for (int i = 0; i < N; i++) {
		scanf("%d", &x);

		// To find if we have the value of
		// 10 000 - x, we need to subtract x fror 10 000. 10 000 in our
		// array is 10000 + 32768 = 42768
		x = 42768 - x;
		//
		// If we have some thing at this spot, we are good.
		if (x >= 0 && x < 65536 && have[x]) {
			found = true;
		}

	}

	if (found) {
		printf("YES\n");
	} else {
		printf("NO\n");
	}

	return 0;
}
