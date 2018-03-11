/*
 * p1001 - reverse root
 */
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define BUFFSIZE 2000

int main() {
	uint32_t buff[BUFFSIZE];
	int32_t N = 0;
	
	int rc;
	uint32_t tmp;
	rc = scanf("%u", &tmp);
	while (rc != EOF) {
		buff[N] = tmp;
		N++;
		rc = scanf("%u", &tmp);
	}

	// We are now done.
	for (int32_t i = N-1; i >= 0; i--) {
		float f = sqrtf(buff[i]);
		printf("%.6f\n", f);
	}
	return 0;
}
