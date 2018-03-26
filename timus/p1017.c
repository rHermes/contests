/*
 * p1017 - Staircases
 *
 * This is solved rather simply, by realizing that for each position,
 * we have the choice if either going up or up and to the right.
 *
 * With memorization, this goes fast :)
 *
 */

#include <stdio.h>
#include <inttypes.h>

// You can calculate the max len by seeing which of the triangle
// numbers is the smallest one to fit the MAXN. the nth-triangle
// number has the value of (n*(n+1))/2. 
// To find MAXLEN from MAXN, you can use the formula:
//
// MAXLEN =  (sqrt(1 + 8*MAXN) - 1) / 2

#define MAXN 500
#define MAXLEN 32

// This is stored as ans + 1, so that if we get a negative answer,
// we can still store that we got an answer.
// Might be better to switch this over, as it might give better
// cache locality.
uint64_t F_mem[MAXN+1][MAXLEN+1] = {0};

uint64_t G(int n, int length) {
	if (length < 2) {
		return 0;
	}

	if (F_mem[n][length]) {
		return F_mem[n][length]-1;
	}

	// We solve it for the 2 case, which is simple.
	if ( length == 2 ) {
		uint64_t ans = (n / 2) - (1 - (n % 2));
		F_mem[n][length] = ans + 1;
		return ans;
	} else {
		if (n - length > 0) {
			// Now here is the thing. either we go up or we go right.
			// So the total amount of stairs is UP + UP-RIGHT
			uint64_t ans = G(n-length, length) + G(n-length, length-1);

			F_mem[n][length] = ans + 1;

			return ans;
		} else {
			F_mem[n][length] = 1;
			return 0;
		}
	}
}

// Ok so if we have a function G(n, length)
// then F(n) = G(n,2) + G(n,3) + G(n,4) + G(n,5) + ....
uint64_t F(int n) {
	uint64_t ans = 0;
	for (int i = 2; i <= MAXLEN; i++) {
		uint64_t tmp = G(n, i);
		if (tmp == 0) {
			break;
		} else {
			ans += tmp;
		}
	}
	return ans;
}

int main() {
	int N;
	scanf("%d", &N);
	printf("%" PRIu64 "\n", F(N));
	return 0;
}
