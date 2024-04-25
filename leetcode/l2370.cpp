#include <iostream>
#include <string>
#include <array>
#include <algorithm>

class Solution {
public:
	int longestIdealString(std::string s, int k) {
		std::array<int, 'z' - 'a' + 1> best{};

		for (auto it = s.rbegin(); it != s.rend(); it++) {
			const int c = *it - 'a';
			const int cur = ++best[c];

			// The question now is just if
			const auto low = static_cast<std::size_t>(std::max(0, c - k));
			const auto hi =
				std::min(best.size(), static_cast<std::size_t>(c + k + 1));

			for (std::size_t i = low; i < hi; i++) {
				best[i] = std::max(best[i], cur);
			}
		}
		return *std::max_element(best.cbegin(), best.cend());
	}
};

static auto _ = []() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	return 0;
}();

int main() {}
