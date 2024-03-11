#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cinttypes>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using UT = std::uint64_t;
using ST = std::int64_t;

void solve() {
	UT N = 0;
	UT M = 0;
	UT K = 0;
	std::cin >> N >> M >> K;
	std::vector<UT> left(N);
	std::vector<UT> right(M);

	for (UT i = 0; i < N; i++)
		std::cin >> left[i];

	for (UT i = 0; i < M; i++)
		std::cin >> right[i];

	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	if (right.size() < left.size()) {
		std::swap(right, left);
		std::swap(N, M);
	}

	UT ans = 0;

	for (UT l = 0; l < N; l++) {
		const auto lv = left[l];
		if (K <= lv)
			break;

		const auto maxi = K - lv;

		auto lev = std::upper_bound(right.begin(), right.end(), maxi);
		ans += static_cast<UT>(std::distance(right.begin(), lev));
	}

	std::cout << ans << std::endl;
}

int main() {
	std::cin.tie(0);
	std::cin.sync_with_stdio(false);

	UT T = 0;
	std::cin >> T;

	for (UT t = 0; t < T; t++) {
		solve();
	}
}
