#include <cstdio>
#include <cstdint>
#include <set>

/* using ST = std::int64_t; */
using UT = std::uint32_t;


int main() {
	UT N = 0;
	UT TARGET = 0;
	scanf("%u %u", &N, &TARGET);
	
	// early exit
	if (N == 1) {
		printf("0\n");
		return 0;
	}

	std::set<UT> arr;
	for (UT i = 0; i < N; i++) {
		UT x = 0;
		scanf("%u", &x);
		
		UT alt = TARGET ^ x;
		if (0 < arr.count(alt)) {
			printf("YES\n");
			return 0;
		}
		arr.insert(x);
	}

	printf("NO\n");
	return 0;
}
