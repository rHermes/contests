#include <cstdio>
#include <cstdint>

#include <array>
#include <numbers>
#include <cmath>
#include <unordered_map>

using ST = std::int64_t;
using UT = std::uint64_t;

/* constexpr UT MAX_N = 1000; */
/* constexpr double TOL = 0.0000000000001; */
inline ST pmod(ST i, ST n) {
    return (i % n + n) % n;
}

ST ipow(ST base, UT exp, UT m) {
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


int main(void) {
	UT A, N, P;
	scanf("%lu %lu %lu", &A, &N, &P);

	std::unordered_map<UT,UT> table;
	const UT m = static_cast<UT>(std::ceil(std::sqrt(P)));
	UT aj = 1;
	for (UT j = 0; j < m; j++) {
		table[aj] = j;
		aj = ((aj % P) * (A % P)) % P;
	}

	const UT am = ipow(A, (P-2)*m, P);

	UT yl = N;
	for (UT i = 0; i < m; i++) {
		auto it = table.find(yl);
		if (it != table.end()) {
			printf("%lu\n", i*m + it->second);
			return 0;
		}

		yl = (yl * am) % P;
	}

	printf("DNE\n");
	return 0;
}
