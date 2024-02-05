#include <cstdio>
#include <cstdint>
#include <vector>

using UT = std::uint64_t;
using ST = std::int64_t;

int main(void) {
	UT N = 0;
	UT D = 0;
	ST K = 0;
	UT X = 0;

	scanf("%lu %lu %ld %lu", &N, &D, &K, &X);

	std::vector<UT> speeds(N);
	for (UT i = 0; i < N; i++) {
		UT a = 0;
		scanf("%lu", &a);
		speeds[i] = a;
	}

	UT P = 0;
	scanf("%lu", &P);
	
	for (auto ai : speeds) {
		if (ai < P)
			continue;

		while (P <= ai && 0 <= K) {
			ai = (ai * (100-X)) / 100;
			K -= 1;
		}

		if (K < 0) {
			printf("NO\n");
			break;
		}
	}

	if (0 <= K)
		printf("YES\n");

	return 0;
}
