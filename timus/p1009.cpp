/*
 *  p. 1009 - K-based Numbers
 *
 *
 * I think this can be done recursively, with a function call like:
 *
 * possible(prev_zero, K, left)
 *
 * and then we can just cache that. The first call will just be:
 * possible(true, K, N)
 *
 */

#include <map>
#include <tuple>

#include <stdio.h>
#include <stdint.h>

// This is because my machine uses slightly different scanners than the
// online judge.
#ifdef ONLINE_JUDGE
#define LONG_SCAN "%llu"
#else
#define LONG_SCAN "%lu"
#endif

#define TT uint_fast64_t

TT K;
std::map<TT,TT> zero_mem;
std::map<TT,TT> one_mem;
TT possible(bool prev_zero, TT N) {
	if (N == 1) {
		if (prev_zero) {
			return K-1;
		} else {
			return K;
		}
	}

	// Now we check to see if we have the thingy.
	if (prev_zero) {
		auto search = zero_mem.find(N);
		if (search != zero_mem.end()) {
			return search->second;
		}

		// Here we know we don't have it.
		TT ans = (K-1) * possible(false, N-1);
		zero_mem[N] = ans;
		return ans;
	} else {
		auto search = one_mem.find(N);
		if (search != one_mem.end()) {
			return search->second;
		}
		
		TT ans = possible(true, N-1) + (K-1) * possible(false, N-1);
		one_mem[N] = ans;
		return ans;
	}
}

int main() {
	TT N;
	scanf(LONG_SCAN "\n" LONG_SCAN, &N,&K);

	TT ans = possible(true, N);

	printf(LONG_SCAN "\n", ans);
	return 0;
}
