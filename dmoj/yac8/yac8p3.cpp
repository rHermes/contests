#include <cstdio>
#include <cinttypes>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>

using UT = std::uint64_t;
using ST = std::int64_t;

using Graph = std::unordered_map<UT, std::unordered_set<UT>>;

UT evaluate(
		const UT N,
		/* const std::vector<UT>& P, */
		const std::vector<std::unordered_map<UT,UT>>& M,
		const Graph& G,
		const UT C) {

	// Ok we now have to count the number of ores in a tunnel. This is
	// slow, but I don't know really what else we should do.
	
	std::unordered_set<UT> seen;
	std::queue<UT> Q;

	std::unordered_map<UT,UT> ores;
	Q.push(C);

	while (!Q.empty()) {
		auto cur = Q.front();
		Q.pop();
	
		// Test if we have been to this node before
		if (auto p = seen.emplace(cur); !p.second)
			continue;

		for (const auto& [k, v] : M[cur]) {
			ores[k] += v;
		}

		for (const auto& next : G.at(cur)) {
			Q.push(next);
		}
	}

	/* printf("For C=%lu we have the following ore count:\n", C); */
	/* for (const auto [ore, count] : ores) { */
	/* 	printf("Ore %lu: %lu\n", ore, count); */
	/* } */
	
	// Now we just need to create a sorted vector.
	std::vector<UT> stones;
	for (const auto kv : ores)
		stones.emplace_back(kv.second);

	std::sort(stones.begin(), stones.end());
	
	UT ans = 0;
	for (UT i = 0; i < stones.size(); i++) {
		ans = std::max((stones.size()-i)*stones[i], ans);
	}


	return ans;
}


int main() {
	UT N = 0;
	scanf("%lu", &N);

	std::vector<UT> P(N);
	// we are shifting all numbers by 1, so it's indexed correctly and -1 is outside.
	std::unordered_map<UT, std::unordered_set<UT>> G;
	for (UT i = 0; i < N; i++) {
		UT dst = 0;
		scanf("%lu", &dst);
		P[i] = dst;

		G[dst].emplace(i+1);
		G[i+1].emplace(dst);
	}
	
	// Ores in each chamber.
	std::vector<std::unordered_map<UT,UT>> M(N+1);
	for (UT i = 1; i <= N; i++) {
		UT mi = 0;
		scanf("%lu", &mi);
		for (UT j = 0; j < mi; j++) {
			UT val = 0;
			scanf("%lu", &val);
			M[i][val]++;
		}
	}


	// We have to evaluate the graph for each of the points.
	for (UT c = 1; c <= N; c++) {
		// Remove the tunnel
		G[c].erase(P[c-1]);
		G[P[c-1]].erase(c);

		/* printf("%lu\n", evaluate(N, P, M, G, c)); */
		printf("%lu\n", evaluate(N, M, G, c));
		
		// Insert the tunnel again.
		G[c].emplace(P[c-1]);
		G[P[c-1]].emplace(c);
	}

	return 0;
}
