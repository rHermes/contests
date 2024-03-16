#include <iostream>
#include <map>
#include <vector>
#include <cinttypes>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using UT = std::uint64_t;
using ST = std::int64_t;

void calcIt(
		std::map<std::pair<UT,UT>,std::unordered_set<UT>>& cache,
		const std::string& s,
		const UT l, const UT r, std::unordered_set<UT>& out) {
	std::cout << "Called with: " << l << " and " << r << std::endl;

	if (l == r) {
		return;
	}

	if (l+1 == r) {
		if (s[l] != s[r]) {
			out.insert(2);
		}
		return;
	}

	const auto key = std::make_pair(l, r);
	if (auto it = cache.find(key); it != cache.end()) {
		out.insert(it->second.begin(), it->second.end());
		/* return it->second; */
		return;
	}

	std::unordered_set<UT> love;
	calcIt(cache, s, l, r-1, love);
	calcIt(cache, s, l+1, r, love);
	/* UT ans = std::max(ans1, ans2); */
	// Our widht is atleast 3 here.
	if (s[l] != s[r]) {
		love.insert(r - l + 1);
	}

	cache[key] = love;

	out.insert(love.begin(), love.end());
}

void solve() {
	UT N = 0;
	UT Q = 0;
	std::cin >> N >> Q;
	std::string line;
	std::getline(std::cin >> std::ws, line);


	// ok we try to make a DP here.
	//
	std::map<std::pair<UT,UT>,std::unordered_set<UT>> cache;
	for (UT i = 0; i < Q; i++) {
		UT l = 0;
		UT r = 0;
		std::cin >> l >> r;
		std::unordered_set<UT> love;
		calcIt(cache, line, l-1, r-1, love);
		UT pk = 0;
		for (const auto& p : love)
			pk += p;

		std::cout << pk << std::endl;

	}

}

int main() {
	std::cin.tie(0);
	std::cin.sync_with_stdio(false);

	UT T = 0;
	std::cin >> T;

	for (UT t = 0; t < T; t++) {
		solve();
		/* break; */
	}
}
