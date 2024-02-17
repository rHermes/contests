#include <cstdio>
#include <array>
#include <cinttypes>
#include <vector>
/* #include <iostream> */

using UT = std::uint64_t;
using ST = std::int64_t;

struct Node {
};

int main() {
	UT N = 0;
	UT K = 0;
	scanf("%lu %lu", &N, &K);

	std::vector<UT> FS(N);
	for (UT i = 0; i < N; i++) {
		scanf("%lu", &FS[i]);
	}



	return 0;
}
