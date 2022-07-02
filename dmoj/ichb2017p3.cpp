/*
 * ichb2017p3 - ICHB Selection Contest '17 Problem 3 - Parallel Universe
 *
 * Tried 32 invidual summation tables, but the updates are to slow
 * I think. Going to try a sqrt decomposition now.
 *
 * https://cp-algorithms.com/data_structures/sqrt_decomposition.html#implementation
 *
 * Square decomposition worked, but looking at the faster submissions,
 * it seems that the preferred version is a segment tree. I changed to
 * using a segment tree and now it was much faster:
 *
 * https://cp-algorithms.com/data_structures/segment_tree.html#implementation
 */

#include <cstdio>
#include <cstdint>
#include <array>
#include <limits>

using T = uint_fast32_t; 

constexpr T MAX_N = 100000 + 1;
std::array<T, MAX_N*4 + 1> TREE;
std::array<T, MAX_N> VALUES;

// Build a vertain node. We start at 1
void build(T vertex, T tl, T tr) {
	if (tl == tr)
		TREE[vertex] = VALUES[tl];
	else {
		const T tm = (tl + tr) / 2;

		// Left
		build(vertex*2, tl, tm);
		// Right
		build(vertex*2 + 1, tm+1, tr);

		TREE[vertex] = TREE[vertex*2] & TREE[vertex*2 + 1];
	}
}

T query(T vertex, T tl, T tr, T l, T r) {
	if (l == tl && r == tr) {
		return TREE[vertex];
	}

	const T tm = (tl + tr) / 2;

	if (r <= tm) {
		return query(vertex*2, tl, tm,  l, r);
	} else if (tm < l) {
	   return query(vertex*2 + 1, tm + 1, tr, l, r);
	} else {
		const T left = query(vertex*2, tl, tm,  l, tm);
		const T right = query(vertex*2 + 1, tm + 1, tr, tm + 1, r);
		return left & right;
	}
}

void update(T vertex, T tl, T tr, T pos, T new_val) {
	if (tl == tr)
		TREE[vertex] = new_val;
	else {
		const T tm = (tl + tr) / 2;
		if (pos <= tm)
			update(vertex*2, tl, tm, pos, new_val);
		else
			update(vertex*2+1, tm+1, tr, pos, new_val);

		TREE[vertex] = TREE[vertex*2] & TREE[vertex*2 + 1];
	}

}



int main(void) {
	T N, Q;
	scanf("%lu %lu", &N, &Q);


	for (T i = 1; i <= N; i++) {
		T q;
		scanf("%lu", &q);
		VALUES[i] = q;
	}

	// Build tree
	build(1, 1, N);

	// Now process queries.
	for (T i = 0; i < Q; i++) {
		char c[10];
		scanf("%s", c);

		if (c[0] == 'Q') {
			T x, y, val;
			scanf("%lu %lu %lu", &x, &y, &val);
			printf("%lu\n", query(1, 1, N, x, y) & val);
		} else {
			T x, val;
			scanf("%lu %lu", &x, &val);
			update(1, 1, N, x, val);
		}
	}

	return 0;
}
