/*
 * p1011 - Conductors
 *
 * This seems like something which can be solved with a simple bruteforce.
 *
 * I'll go into this with a really stupid variant and then go from there.
 */
#include <stdio.h>
#include <inttypes.h>
#include <math.h>

double round(double d) {
	return floor(d*10000+0.5)/10000;
}

int main() {
	double P, Q;
	scanf("%lf%lf", &P, &Q);
	P /= 100;
	Q /= 100;


	for (uint32_t people = 2; ; people++) {
		double min = round(people*P);
		double max = round(people*Q);

		uint32_t C = (uint32_t)max;
		if (C > min && C < max && C >= 1) {
			printf("%" PRIu32 "\n", people);
			return 0;
		}
	}

	return 1;
}
