#include <cstdio>
#include <cinttypes>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <set>

using UT = std::uint64_t;
using ST = std::int64_t;

int main() {
	UT N = 0;
	scanf("%lu", &N);

	// we are shifting all numbers by 1, so it's indexed correctly and -1 is outside.
	// This is the list of nodes that point to our node.
	std::vector<std::vector<UT>> G(N);
	for (UT i = 0; i < N; i++) {
		UT dst = 0;
		scanf("%lu", &dst);
		if (dst == 0)
			continue;

		G[dst-1].push_back(i);
	}
	
	// Ores in each chamber.
	std::vector<std::unordered_map<UT,UT>> M(N);
	std::vector<UT> best(N);
	std::vector<std::vector<UT>> gis(N);
	std::vector<UT> totalOres(N);
	for (UT i = 0; i < N; i++) {
		UT mi = 0;
		scanf("%lu", &mi);
		totalOres[i] += mi;

		auto& gi = gis[i];
		for (UT j = 0; j < mi; j++) {
			UT val = 0;
			scanf("%lu", &val);
			auto num = ++M[i][val];

			if (gi.size() <= num)
				gi.resize(num+1);

			gi[num]++;
			best[i] = std::max(best[i], num*gi[num]);
		}
	}
	
	// We now update each node.
	for (ST c = N-1; -1 < c; c--) {
		for (const auto& child : G[c]) {
			if (totalOres[c] < totalOres[child]) {
				std::swap(totalOres[c], totalOres[child]);
				swap(M[c], M[child]);
				gis[c] = std::move(gis[child]);
				best[c] = std::max(best[c], best[child]);
			}
		}

		auto& gi = gis[c];
		for (const auto& child : G[c]) {
			totalOres[c] += totalOres[child];
			for (const auto& [k, v] : M[child]) {
				const auto before = M[c][k];
				const auto num = before + v;
				M[c][k] = num;

				if (gi.size() <= num) {
					gi.resize(num+1);
				}

				for (auto j = before+1; j <= num; j++) {
					gi[j]++;
					best[c] = std::max(best[c], j*gi[j]);
				}
			}
		}
	}

	for (const auto& b : best)
		printf("%lu\n", b);

	return 0;
}
