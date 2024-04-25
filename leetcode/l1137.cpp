#include <array>

constexpr auto tribs = []() {
	std::array<int, 38> all;
	all[0] = 0;
	all[1] = 1;
	all[2] = 1;
	for (std::size_t i = 3; i < all.size(); i++) {
		all[i] = all[i - 3] + all[i - 2] + all[i - 1];
	}

	return all;
}();

class Solution {
public:
	int tribonacci(int n) { return tribs[n]; }
};

int main() { return 0; }
