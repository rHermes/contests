#include <cstdio>
#include <array>
#include <cinttypes>
#include <vector>
/* #include <iostream> */

using UT = std::uint64_t;
using ST = std::int64_t;



int main() {
	UT N = 0;
	scanf("%lu", &N);

	std::vector<UT> AS(N);
	for (UT i = 0; i < N; i++)
		scanf("%lu", &AS[i]);

	std::vector<UT> BS(N);
	for (UT i = 0; i < N; i++)
		scanf("%lu", &BS[i]);

	std::vector<UT> CS(N);
	for (UT i = 0; i < N; i++)
		scanf("%lu", &CS[i]);

	std::vector<UT> DS(N);
	for (UT i = 0; i < N; i++)
		scanf("%lu", &DS[i]);


	return 0;
}
