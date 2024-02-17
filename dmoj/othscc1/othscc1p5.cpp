#include <cstdio>
#include <cstdint>
#include <vector>
#include <unordered_set>
#include <map>
#include <cmath>
#include <queue>
#include <set>
#include <algorithm>

using UT = std::uint64_t;
using ST = std::int64_t;

struct State {
	UT itemsDone{0};
	UT position{0};

	auto operator<=>(const State& rhs) const = default;
};

struct Node {
	UT time{0};
	UT itemsDone{0};
	UT position{0};

	Node(UT ti, UT doo, UT pos) : time{ti}, itemsDone{doo}, position{pos} {};

	friend constexpr std::strong_ordering operator<=>(const Node& l, const Node& r) {
		if (l.time != r.time)
			return l.time<=>r.time;

		if (l.itemsDone != r.itemsDone)
			return r.itemsDone<=>l.itemsDone;

		return l.position<=>r.position;
	};
};

std::map<std::pair<UT,UT>,UT> CACHE;
// introduce caching here maybe.
/* UT minCost(const std::vector<std::map<UT,UT>>& G, const UT src, const UT dst) { */
UT minCost(const std::vector<std::vector<std::pair<UT,UT>>>& G, const UT src, const UT dst) {
	if (src == dst)
		return 0;
	
	std::pair<UT,UT> key{std::min(src,dst), std::max(src,dst)};
	if (auto it = CACHE.find(key); it != CACHE.end()) {
		return it->second;
	}

	using P = std::pair<UT,UT>;
	std::set<UT> seen;
	std::priority_queue<P, std::vector<P>, std::greater<P>> Q;
	// score, pos
	Q.emplace(0, src);
	while (!Q.empty()) {
		const auto [score, cur] = Q.top();
		Q.pop();

		if (cur == dst) {
			CACHE[key] = score;
			return score;
		}

		if (auto it = seen.insert(cur); !it.second)
			continue;

		for (const auto& [next, cost] : G[cur]) {
			if (!seen.count(next)) {
				Q.emplace(score + cost, next);
			}
		}
	}

	return 100000000000000;
}

int main() {
	UT N = 0;
	UT M = 0;
	UT K = 0;
	scanf("%lu %lu %lu\n", &N, &M, &K);

	std::vector<UT> createTime(K);
	for (UT i = 0; i < K; i++) {
		scanf("%lu", &createTime[i]);
	}

	std::vector<std::vector<UT>> itemLocs(K);
	for (UT i = 0; i < K; i++) {
		UT x = 0;
		scanf("%lu", &x);
		itemLocs[i].resize(x);
	}

	for (UT i = 0; i < K; i++) {
		for (UT j = 0; j < itemLocs[i].size(); j++) {
			scanf("%lu", &itemLocs[i][j]);
			itemLocs[i][j]--;
		}
	
		// we need it for a binary search later.
		std::sort(itemLocs[i].begin(), itemLocs[i].end());
	}


	/* std::vector<std::map<UT,UT>> G(N); */
	std::vector<std::vector<std::pair<UT, UT>>> G(N);

	for (UT i = 0; i < M; i++) {
		UT a, b, c;
		scanf("%lu %lu %lu", &a, &b, &c);

		G[a-1].emplace_back(b-1, c);
		G[b-1].emplace_back(a-1, c);
		/* G[a-1][b-1] = c; */
		/* G[b-1][a-1] = c; */
	}

	std::set<State> seen;
	std::priority_queue<Node,std::vector<Node>,std::greater<Node>> Q;
	Q.emplace(0,0,0);
	while (!Q.empty()) {
		const auto cur = Q.top();
		Q.pop();

		if (cur.itemsDone == K) {
			printf("%lu\n", cur.time);
			break;
		}
		
		//  Skip if we have been here before.
		if (auto it = seen.emplace(cur.itemsDone, cur.position); !it.second) {
			continue;
		}

		/* printf("We are at node %lu %lu %lu\n", cur.time, cur.itemsDone, cur.position); */
		
		const auto& locs = itemLocs[cur.itemsDone];
		if (std::binary_search(locs.begin(), locs.end(), cur.position)) {
			// we always skip if the items are in the current position.
			Q.emplace(cur.time, cur.itemsDone+1, cur.position);
		} else {
			// Time, done, pos
			// Stay in the same place and craft.
			Q.emplace(cur.time + createTime[cur.itemsDone], cur.itemsDone+1, cur.position);

			for (const auto& dst : locs) {
				const auto dirCost = minCost(G, cur.position, dst);

				Q.emplace(cur.time + dirCost, cur.itemsDone+1, dst);
			}
		}
	}

	return 0;
}
