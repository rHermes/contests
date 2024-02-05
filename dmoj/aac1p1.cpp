#include <cstdio>
#include <cstdint>

using UT = std::uint64_t;

int main(void) {
	UT S = 0;
	UT R = 0;

	scanf("%lu %lu", &S, &R);

	if (S*S*100 < R*R*314)
		printf("CIRCLE\n");
	else
		printf("SQUARE\n");

	return 0;
}
