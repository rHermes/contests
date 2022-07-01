/*
 * ichb2017p2 - ICHB Selection Contest '17 Problem 2 - Black Star's Visit
 *
 * This is a fun task, where the clue is to realize that you can calculate
 * the following properties for a given city:
 *
 * - Total number of citizens
 * - Number of horizontally symmetrical numbers
 * - Number of vertically symmetrical numbers
 * - Number of both vertically and horizontally symmetrical numbers.
 *
 * I first solved this using modular exponentiation, which was quite fast,
 * but I looked at the best submissions and they utilized the fact that
 * since we only use two bases, and almost every exponent in the space,
 * it's worth just precalculating the entire table.
 *
 * The number of horizontally symmetrical numbers are simply any
 * number consisting only of the digits 0, 1 and 8. 
 *
 * I thought I could do one better and constexpr the entire thing, but I
 * hit the step limit.
 */

#include <cstdio>
#include <cstdint>
#include <array>

using T = int_fast64_t; 

constexpr T MAX_N = 1000000 + 1;
constexpr T M = 666013;


inline constexpr T positive_modulo(T i, T n) {
    return (i % n + n) % n;
}

std::array<T, MAX_N> POW3;
std::array<T, MAX_N> POW10;

int main(void) {
	int N, Q;
	scanf("%d %d", &N, &Q);


	POW3[0] = 1;
	POW10[0] = 1;

	// Precalculate powers
	for (int i = 1; i < MAX_N; i++) {
		POW3[i] = (POW3[i-1]* 3) % M;
		POW10[i] = (POW10[i-1]* 10) % M;
	}

	for (int i = 0; i < Q; i++) {
		T q;
		scanf("%ld", &q);

		const T total = 9 * POW10[q-1] % M;
		
		const T palin = 9 * POW10[(q-1) / 2];
		const T vert  = 2 * POW3[q-1];
		const T both = 2 * POW3[(q-1) / 2];

		const T hated = positive_modulo(total - palin - vert + both, M);

		printf("%ld\n", hated);
	}

	return 0;
}
