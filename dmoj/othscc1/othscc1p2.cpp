#include <iostream>
#include <cstdint>

using UT = std::uint64_t;
int main() {
	UT N;
	std::cin >> N;

	UT mmax = 0;
	UT sum = 0;
	for (UT i = 0; i < N; i++) {
		UT x;
		std::cin >> x;
		mmax = std::max(mmax, x);
		sum += x;
	}

	std::cout << (sum-mmax)/(N-1) << std::endl;
	return 0;
}
