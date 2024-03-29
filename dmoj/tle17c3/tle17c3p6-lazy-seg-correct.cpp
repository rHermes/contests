#include <cstdio>
#include <cstdint>

#include <stdexcept>

#include <tuple>
#include <array>
#include <vector>
#include <deque>

using UT = std::uint64_t;
using ST = std::int64_t;

constexpr ST MAX_N = 100000 + 5;
constexpr ST MAX_K = 10;
constexpr ST MOD_M = 1000000007;
/* constexpr UT MAX_K = 3; */

ST NN = 10;

inline ST pmod(ST i, ST n) {
    return (i % n + n) % n;
}

ST ipow(ST base, ST exp, ST m) {
	ST res = 1;
	base = pmod(base, m);

	if (base == 0)
		return 0;


	while (exp > 0) {
		if (exp % 2 == 1)
			res = pmod(res * base, m);

		exp >>= 1;
		base = pmod(base*base, m);
	}

	return res;
}


struct Node {
	ST value{0};
	bool is_lazy{false};
	// This is (l, r, k, original_l) for the update values.
	std::tuple<UT, UT, UT, UT> lazy_val{0, 0, 0, 0};
};

/* std::vector<std::vector<UT>> ranges; */
std::array<std::array<ST, MAX_N+1>, MAX_K+1> ranges;
std::array<Node, 4*(MAX_N+1)> TREE;

void push_down(UT v, ST tl, ST tr) {
	auto& nd = TREE[v];
	if (!nd.is_lazy)
		return;

	auto [il, ir, ik, ioffset] = nd.lazy_val;

	// The value always increased by this
	/* nd.value = pmod(nd.value + (ranges[ik][ir-ioffset] - ranges[ik][il-ioffset]), MOD_M); */
	nd.value = pmod(nd.value + (ranges[ik][ir-ioffset+1] - ranges[ik][il-ioffset]), MOD_M);
	/* nd.value = pmod(nd.value + (ranges[ik][ir-il+1]), MOD_M); */
	nd.is_lazy = false;

	// If we are at the end of a node, that's it for us.
	if (tl == tr)
		return;

	const ST tm = (tl + tr) / 2;

	if (ir <= static_cast<UT>(tm)) {
		// The entire update range is on the left, we go down there
		push_down(v*2, tl, tm);
		TREE[v*2].is_lazy = true;
		TREE[v*2].lazy_val = {il, ir, ik, ioffset};
	} else if (static_cast<UT>(tm) < il) {
		// The entire update range is on the right
		push_down(v*2 + 1, tm+1, tr);
		TREE[v*2 + 1].is_lazy = true;
		TREE[v*2 + 1].lazy_val = {il, ir, ik, ioffset};
	} else {
		// They are both touched by the update, we push down both
		// and update both.
		push_down(v*2, tl, tm);
		TREE[v*2].is_lazy = true;
		TREE[v*2].lazy_val = {il, tm, ik, ioffset};

		push_down(v*2 + 1, tm+1, tr);
		TREE[v*2 + 1].is_lazy = true;
		TREE[v*2 + 1].lazy_val = {tm+1, ir, ik, ioffset};
	}
}

/* void update(UT v, UT tl, UT tr, UT l, UT r, UT k) { */
/* } */

void update(ST l, ST r, ST k) {
	/* update(1, 1, MAX_N, l, r, k); */
	// We push down the top
	push_down(1, 1, NN);
	// Add lazy
	TREE[1].is_lazy = true;
	TREE[1].lazy_val = {l, r, k, l};
}

ST query(UT v, ST tl, ST tr, ST l, ST r) {
	push_down(v, tl, tr);

	auto& nd = TREE[v];
	if (tl == l && tr == r)
		return nd.value;

	const ST tm = (tl + tr) / 2;

	if (r <= tm) {
		// The entire update range is on the left, we go down there
		return query(v*2, tl, tm, l, r);
	} else if (tm < l) {
		// The entire update range is on the right
		return query(v*2+1, tm+1, tr, l, r);
	} else {
		const ST left = query(v*2, tl, tm, l, tm);
		const ST right = query(v*2 + 1, tm+1, tr, tm+1, r);
		return pmod(left + right, MOD_M);
	}
}

ST query(ST l, ST r) {
	return query(1, 1, NN, l, r);
}

void print_it() {
	std::deque<std::pair<ST,ST>> Q;
	Q.push_back({1, NN});

	while (!Q.empty()) {
		auto [l, r] = Q.front();
		Q.pop_front();

		printf("[%ld - %ld]: %ld\n", l, r, query(l, r));
		if (l == r)
			continue;

		const ST tm = (l + r) / 2;
		Q.push_back({l, tm});
		Q.push_back({tm+1, r});
	}
}


int main(void) {
	ST N, Q;
	scanf("%ld %ld", &N, &Q);
	NN = N;

	// We precompute the ranges
	for (UT k = 0; k <= MAX_K; k++) {
		ranges[k][0] = 0;

		for (UT i = 1; i <= MAX_N; i++) {
			ranges[k][i] = pmod(ipow(static_cast<ST>(i), static_cast<ST>(k), MOD_M) + ranges[k][i-1], MOD_M);
		}
	}

	// We print a little thing:
	/* for (UT i = 0; i <= N; i++) { */
	/* 	printf("sum(%lu,%lu) = %lu\n", 1ul, i, ranges[1][i]); */
	/* } */


	char buf[5];
	for (ST i = 0; i < Q; i++) {
		scanf("%s", buf);
		if (buf[0] == 'U') {
			ST l, r, k;
			scanf("%ld %ld %ld", &l, &r, &k);
			/* printf("Adding %lu %lu %lu, with a sum of %lu\n", l, r, k, ranges[k][r-l+1]); */
			/* printf("BEFORE:\n"); */
			/* print_it(); */
			update(l, r, k);
			/* printf("AFTER:\n"); */
			/* print_it(); */
		} else {
			ST l, r;
			scanf("%ld %ld", &l, &r);
			printf("%ld\n", query(l, r));
		}
	}

	return 0;
}
