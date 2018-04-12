/*
 * p1036 - Lucky Tickets
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50
#define MAX_S 1000
#define MAX_S_HALF 500

// The vaulues here can be very big, but they only test for about 12. This is funny as one would
// think they would take the time to get the biggest values. But 11 works here. For completeness,
// we could make this a higher number, but that leads to slower solve times.
#define BIG_MAX 11
#define BIG_BASE 1000000000

/* Slow bigint implementation, that gets the job done. */
typedef uint32_t BIG[BIG_MAX];

// This adds big a and b together.
void BIG_add(BIG const a, BIG const b, BIG c) {
        uint32_t carry = 0;
        for (int i = 0; i < BIG_MAX; i++) {
                uint64_t tmp = (uint64_t)a[i] + (uint64_t)b[i] + carry;
                c[i] = tmp % BIG_BASE;
                carry = tmp / BIG_BASE;
        }
}

// This multiplies a * b into c
void BIG_mul(BIG a, uint32_t wow) {
        uint32_t carry = 0;
        for (int i = 0; i < BIG_MAX; i++) {
                uint64_t tmp = wow*(uint64_t)a[i] + carry;
                a[i] = tmp % BIG_BASE;
                carry = tmp / BIG_BASE;
        }
}
// This multiplies a * b into c
void BIG_mul_too(BIG const a, uint32_t wow, BIG c) {
        uint32_t carry = 0;
        for (int i = 0; i < BIG_MAX; i++) {
                uint64_t tmp = wow*(uint64_t)a[i] + carry;
                c[i] = tmp % BIG_BASE;
                carry = tmp / BIG_BASE;
        }
}

// Slow long multiplication, but since we only use it once,
// it is ok.
void BIG_bmul(BIG const a, BIG const b, BIG c) {
	BIG tmp;

	// Zero C?
	memset(c, 0, sizeof(BIG));

	for (int i = 0; i < BIG_MAX; i++) {
		// firs we simply set this to 0.
		BIG_mul_too(a, b[i], tmp);

		// Then for each spot on rang, we need to add the base.
		for (int j = 0; j < i; j++) {
			BIG_mul(tmp, BIG_BASE);
		}

		BIG_add(c, tmp, c);
	}
}

// We only need two, since this is
BIG row1[MAX_S_HALF+1];
BIG row2[MAX_S_HALF+1];

char buff[16];
int main() {
	char *tmp = fgets(buff, sizeof(buff), stdin);
	unsigned long n = strtoul(tmp, &tmp, 10);
	unsigned long s = strtoul(tmp, NULL, 10);

	if (s == 0) {
		printf("1\n");
		return 0;
	}

	if (s % 2 != 0) {
		printf("0\n");
		return 0;
	}
	
	// We can also check if the target is out of size of 2*9*n.
	if (s > 2*9*n) {
		printf("0\n");
		return 0;
	}

	const unsigned long s2 = s/2;
	
	// This makes it faster to alternate between the two.
	BIG *prev = row1;
	BIG *cur = row2;


	// Ok, now we need to start from n = 0 and move our way up.
	// only thing that is 1 on n = 0 is s = 0.
	prev[0][0] = 1;

	for (int j = 1; j <= n; j++) {
		// goal = 0; is always 1. We zero out then set 1
		memset(cur[0], 0, sizeof(BIG));
		cur[0][0] = 1;
		
		for (int goal = 1; goal <= s2; goal++) {
			// Zero out the current one.
			memset(cur[goal], 0, sizeof(BIG));

			const int lim = (goal > 9) ? 9 : goal;
			for (int i = 0; i <= lim; i++) {
				BIG_add(prev[goal-i], cur[goal], cur[goal]);
			}
		} 
		// Now we switch the previous and the current.
		BIG *tmp = prev;
		prev = cur;
		cur = tmp;
	}

	BIG ans;
	BIG_bmul(prev[s2], prev[s2], ans);

	// Now the answer is in pb1. We figure it out by finding the length.
	int length;
	for (length = BIG_MAX-1; !ans[length] && length >= 0; length--) {}

	
	
	printf("%" PRIu32, ans[length--]);
	while (length >= 0) {
		printf("%.9" PRIu32, ans[length--]);
	}
	printf("\n");
	
	return 0;
}
