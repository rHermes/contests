/*
 * p1026 - Questions and Answers
 *
 * It seems that it is just a matter of sorting and then answering?
 *
 * Since the possible values for the keys are just from 1 to 5000, we can use
 * a counting sort here. Further, we don't have to actually do the sorting part,
 * since we are only going to get a few queries. We can just iterate over the
 * elements of the counting array until we get too the number we want.
 */

#include <stdio.h>
#include <inttypes.h>

#define MAXM 5000
uint16_t db[MAXM+1] = {0};

int main() {
	// Building the database.
	uint_fast32_t N;
	scanf("%" SCNuFAST32, &N);

	for (uint_fast32_t i = 0; i < N; i++) {
		uint16_t a;
		scanf("%" SCNu16, &a);
		db[a]++;
	}
	
	// We skip the three idiots and a whitespace.
	fseek(stdin, 4, SEEK_CUR);
	// Now get the amount of queries.
	uint_fast8_t K;
	scanf("%" SCNuFAST8, &K);

	for (uint_fast8_t i = 0; i < K; i++) {
		int_fast32_t a;
		scanf("%" SCNdFAST32, &a);

		// We now loop through the program until a becomes negative.
		uint_fast16_t j;
		for (j = 1; a > 0; a -= db[j], j++);
		printf("%" PRIuFAST16 "\n", j-1);
	}

	return 0;
}
