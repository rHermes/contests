#include <iostream>
#include <cstdint>

int main() {
	std::uint64_t A, B;
	std::cin >> A >> B;
	if (A == 0 || B == 0)
		std::cout << 0 << std::endl;
	else
		std::cout << A+B << std::endl;

	return 0;
}
