#include <cstdio>
#include <cstdint>

int main() {
	std::uint32_t T = 0;
	scanf("%u", &T);

	for (std::uint32_t i = 0; i < T; i++) {
		std::uint32_t N = 0;
		scanf("%u", &N);
	
		if (N == 2) {
			printf("2\n");
		} else {
			printf("%u\n", N-1);
		}
	}

	return 0;
}
