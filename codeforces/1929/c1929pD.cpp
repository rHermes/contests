#include <cstdio>
#include <cinttypes>

#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <cmath>

using UT = std::uint64_t;
using ST = std::int64_t;

constexpr UT MOD_M = 998244353;

int main() {
	UT T = 0;
	scanf("%lu", &T);

	for (UT t = 0; t < T; t++) {
		UT N = 0;
		scanf("%lu", &N);

		std::vector<UT> node(N);
		for (UT i = 0; i < N-1; i++) {
			scanf("%lu", &node[i]);
			node[i]--;
		}
	}
	return 0;
}
