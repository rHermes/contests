/*
 * p1001 - reverse root
 */
#include <stdio.h>
#include <math.h>
#include <inttypes.h>

int main() {
	double buff[128*1024];
	int32_t N = 0;
	
	int rc;
	uint64_t tmp;
	rc = scanf("%" SCNu64, &tmp);
	while (rc != EOF) {
		buff[N] = sqrt(tmp * 1.0);
		N++;
		rc = scanf("%" SCNu64, &tmp);
	}

	// We are now done.
	for (int32_t i = N-1; i >= 0; i--) {
		printf("%.4lf\n", buff[i]);
	}

	return 0;
}
