/*
 * p1110 - Power
 *
 * This seems like a simple modular exponention problem.
 */

#include <stdio.h>
#include <inttypes.h>

#define TT uint_fast32_t

TT modular_pow(TT base, TT exponent, TT modulus) {
	if (modulus == 1) {
		return 0;
	}
	TT result = 1;

	base %= modulus;

	while (exponent > 0) {
		if (exponent % 2 == 1) {
			result = (result * base) % modulus;
		}

		exponent >>= 1;
		base = (base * base) % modulus;
	}

	return result;
}

int main() {
	TT N, M, Y;

	// Get input.
	scanf("%" SCNuFAST32 " " "%" SCNuFAST32 " " "%" SCNuFAST32, &N, &M, &Y);
	
	// Here we just check that Y isn't larger than M. Because if it is,
	// we know there are no numbers that will equal that.
	if (M < Y) {
		printf("-1\n");
		return 0;
	}
	
	char any = 0;
	for (TT X = 0; X < M; X++) {
		if (modular_pow(X, N, M) == Y) {
			any = 1;
			printf("%" PRIuFAST32 " ", X);
		}
	}

	if (!any) {
		printf("-1");
	}

	printf("\n");

	return 0;
}

