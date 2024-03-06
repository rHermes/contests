#include <iostream>
#include <cmath>

int constructiveNumbers(int n) {
	const int maxS = static_cast<int>(std::ceil((1.0 + std::sqrt(1.0 + 8.0*n))/2.0));
	/* std::cout << "maxS is " << maxS << std::endl; */
	
	int ans = 1;
	for (int s = 2; s <= maxS; s++) {
		const int above = 2*n - (s-1)*s;
		const int below = 2*s;
		if (0 < above && above % below == 0) {
			/* std::cout << "FOR input=" << n << " and s=" << s << " a solution is: " << above / below << std::endl; */
			ans++;
		}
	}
	return ans;
}

int main() {
	std::cout << constructiveNumbers(5) << std::endl;
	std::cout << constructiveNumbers(9) << std::endl;
	std::cout << constructiveNumbers(15) << std::endl;
	std::cout << constructiveNumbers(1000000000) << std::endl;
	return 0;
}
