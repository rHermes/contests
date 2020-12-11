/*
 * The ratio between two circles rotation with radius r1 and r2 can be found
 * by understanding that the distance traveled around the circumference of one
 * circle has to be matched by the other. We get the ratio then by setting this
 * up as:
 *
 * r1 * 2 * Pi = x * (r2 * 2 * Pi) <=> x = r1 / r2
 *
 * From here we can reduce the fraction with a gcd.
 */
#include <stdio.h>

int gcd(int a, int b) {
	while (b != 0) {
		int t = b;
		b = a % b;
		a = t;
	}
	return a;
}


int main(void) {
	int N;
	int buf[100];

	if(scanf("%d", &N) != 1 || N > 100 ) {
		perror("invalid input");
		return 1;
	}

	for (int i = 0; i < N; i++) {
		if(scanf("%d", &buf[i]) != 1) {
			perror("invalid input");
			return 1;
		}
	}

	int first = buf[0];


	for (int i = 1; i < N; i++) {
		int r = buf[i];
		int g = gcd(first, r);
		printf("%d/%d\n", first / g, r / g);
	}


	return 0;
}
