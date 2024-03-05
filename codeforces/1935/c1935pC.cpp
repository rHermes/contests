#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cinttypes>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>

using UT = std::uint64_t;
using ST = std::int64_t;

void solve() {
	UT N = 0;
	UT L = 0;
	std::cin >> N >> L;

	std::vector<std::pair<UT,UT>> vals(N);
	for (UT i = 0; i < N; i++) {
		std::cin >> vals[i].second >> vals[i].first;
	}

	std::sort(vals.begin(), vals.end());
	
	UT ans = 0;
	for (UT l = 0; l < N; l++) {
		std::priority_queue<UT> s;
		UT cur = 0;
		for (UT r = l; r < N; r++) {
			// we have the possibility of inserting a.
			s.emplace(vals[r].second);
			cur += vals[r].second;

			// While we are going.
			while (!s.empty() && L < (vals[r].first - vals[l].first + cur)) {
				auto max_value = s.top();
				s.pop();
				cur -= max_value;
			}

			ans = std::max(ans, s.size());
		}
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
