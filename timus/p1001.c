/*
 * p1001 - reverse root
 */
#include <stdio.h>
#include <stdint.h>
#include <math.h>


// We need this, because my machine has a different
// style than the online judge, which is 32bit.
#ifdef ONLINE_JUDGE
#define LONG_SCAN "%llu"
#else
#define LONG_SCAN "%lu"
#endif

int main() {
	double buff[128*1024];
	int32_t N = 0;
	
	int rc;
	uint64_t tmp;
	rc = scanf(LONG_SCAN, &tmp);
	while (rc != EOF) {
		buff[N] = sqrt(tmp * 1.0);
		N++;
		rc = scanf(LONG_SCAN, &tmp);
	}

	// We are now done.
	for (int32_t i = N-1; i >= 0; i--) {
		printf("%.4lf\n", buff[i]);
	}

	return 0;
}
