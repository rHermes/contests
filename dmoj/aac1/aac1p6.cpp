#include <cstdio>
#include <cstdint>
#include <vector>
#include <algorithm>

using UT = std::uint64_t;
using ST = std::int64_t;

#include <map>
#include <unordered_set>
#include <set>

template <typename T>
using SETT = std::set<T>;
/* using SETT = std::unordered_set<T>; */

int main() {
	UT N = 0;
	scanf("%lu", &N);

	std::vector<std::pair<UT,UT>> alpacas(N);
	std::multimap<UT, UT> centers;
	for (UT i = 0; i < N; i++) {
		UT a = 0;
		UT b = 0;
		scanf("%lu %lu", &a, &b);
		alpacas[i] = {a, b};
		centers.emplace(a, i);
	}
	
	using LT = std::pair<UT,SETT<UT>>;
	std::vector<LT> blocks(N);
	for (UT i = 0; i < N; i++) {
		blocks[i].first = i;
		/* printf("Checking alpacca %lu\n", i); */
		const auto& [a, b] = alpacas[i];

		ST mmin = std::max(static_cast<ST>(a)-static_cast<ST>(b)+1, 0L);
		ST mmax = static_cast<ST>(a)+static_cast<ST>(b)-1;
	
		// The first element is the one we are blocking.
		auto it = centers.lower_bound(static_cast<UT>(mmin));
		const auto end = centers.upper_bound(static_cast<UT>(mmax));

		for (; it != end; it++) {
			if (it->second == i)
				continue;
			/* printf("Alpaca %lu blocks %lu\n", i, it->second); */
			// We block it.
			blocks[i].second.insert(it->second);
			// It blocks us
			blocks[it->second].second.insert(i);
			/* blocked.emplace_back(it->second); */
		}
	}

	/* for (const auto& [a,  blk] : blocks) { */
	/* 	printf("Alp %ld blocks:\n", a); */
	/* 	for (const auto& x : blk) { */
	/* 		printf("  %ld\n", x); */
	/* 	} */
	/* } */

	// We sort the vector based on size
	std::sort(blocks.begin(), blocks.end(),
			[](const LT& a, LT& b) { return a.second.size() < b.second.size(); });

	SETT<UT> taken;
	std::vector<UT> picked;
	/* for (auto& p : blocks ) { */
	for (auto& [idx, blocked] : blocks) {
		/* auto idx = p.first; */
		if (taken.count(idx))
			continue;

		/* taken.insert(idx); */
		picked.push_back(idx);
		
		taken.merge(blocked);
	}


	printf("%lu\n", picked.size());
	return 0;
}
