/*
 * ichb2017p3 - ICHB Selection Contest '17 Problem 3 - Parallel Universe
 *
 * Tried 32 invidual summation tables, but the updates are to slow
 * I think. Going to try a sqrt decomposition now.
 *
 * https://cp-algorithms.com/data_structures/sqrt_decomposition.html#implementation
 *
 * Square decomposition worked, but looking at the the faster submissions,
 * it seems that the prefered version is a a segment tree
 */

#include <cstdio>
#include <cstdint>
#include <array>
#include <cmath>
#include <limits>

using T = uint_fast32_t; 

constexpr T MAX_N = 100000 + 1;
// This is the sqrt(MAX_N)
constexpr T MAX_S = 317;

std::array<T, MAX_N> VALUES;
std::array<T, MAX_S> BLOCKS;


int main(void) {
	BLOCKS.fill(std::numeric_limits<T>::max());
	T N, Q;
	scanf("%lu %lu", &N, &Q);

	const T S = static_cast<T>(std::ceil(std::sqrt(N)));

	for (T i = 1; i <= N; i++) {
		T q;
		scanf("%lu", &q);

		VALUES[i] = q;
		BLOCKS[i / S] &= q;
	}

	// Now process queries.
	for (T i = 0; i < Q; i++) {
		char c[10];
		scanf("%s", c);

		if (c[0] == 'Q') {
			T x, y, val;
			scanf("%lu %lu %lu", &x, &y, &val);

			T ans = val;
			T c_l = x / S;
			T c_r = y / S;

			if (c_l == c_r) {
				for (T j = x; j <= y; j++) {
					ans &= VALUES[j];
				}
			} else {
				for (T j = x, end = (c_l+1)*S - 1; j <= end; j++)
					ans &= VALUES[j];

				// Middle blocks
				for (T j = c_l+1; j <= c_r-1; j++)
					ans &= BLOCKS[j];

				// Tail block
				for (T j = c_r*S; j <= y; j++)
					ans &= VALUES[j];
			}


			printf("%lu\n", ans);
		} else {
			T x, val;
			scanf("%lu %lu", &x, &val);

			// We update the values array
			VALUES[x] = val;

			const T block = x / S;
			BLOCKS[block] = std::numeric_limits<T>::max();

			// Then we update the block
			for (T j = block*S, end = (block+1)*S; j < end; j++) {
				BLOCKS[block] &= VALUES[j];
			}
		}
	}



	return 0;
}
