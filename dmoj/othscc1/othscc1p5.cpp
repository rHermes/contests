/** 
 * othscc1p5 - OTHS Coding Competition 1 (Mock CCC) J5 - Scavenger Hunt
 *
 * This is basically a "virtualgraph" search, but the cool things I want
 * to point out here, is that I learned in this task, that when doing
 * this sort of virtual graph search, it can be better to do all intermediate
 * steps, rather than skipping them, as they can have the effect of pruning the
 * graph.
 *
 * In the beginning I would calculate the shortest path between current
 * position and the buildings where the items where in one go, and then just
 * added the end result to the queue again. This gives correct results, but it's
 * slower than actually just adding all the neighbouring nodes to the queue
 * and going again. This is because we are able to prune out suboptimal results
 * earlier with this approach.
 *
 * I learned a lot from this, cool task!
 */
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

template <typename T, typename... Rest>
void hash_combine(std::size_t& seed, const T& v, const Rest&... rest)
{
  if constexpr (sizeof(size_t) >= 8) {
    seed ^= std::hash<T>{}(v) + 0x517cc1b727220a95 + (seed << 6) + (seed >> 2);
  } else {
    seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	(hash_combine(seed, rest), ...);
}

struct State {
	UT itemsDone{0};
	UT position{0};

	auto operator<=>(const State& rhs) const = default;
};

template<>
struct std::hash<State>
{
	std::size_t operator()(const State& s) const noexcept {
		std::size_t seed = 0;
		hash_combine(seed, s.itemsDone, s.position);
		return seed;
	}
};



struct Node {
	UT time{0};
	UT itemsDone{0};
	UT position{0};

	Node(UT ti, UT doo, UT pos) : time{ti}, itemsDone{doo}, position{pos} {};

	// This ordering is to make sure we sort by time first, then itemsDone descending
	// and then we just throw in position, because it doesn't really matter at that point.
	friend constexpr std::strong_ordering operator<=>(const Node& l, const Node& r) {
		if (l.time != r.time)
			return l.time<=>r.time;

		if (l.itemsDone != r.itemsDone)
			return r.itemsDone<=>l.itemsDone;

		return l.position<=>r.position;
	};
};

int main() {
	UT N = 0;
	UT M = 0;
	UT K = 0;
	scanf("%lu %lu %lu\n", &N, &M, &K);

	std::vector<UT> createTime(K);
	for (UT i = 0; i < K; i++) {
		scanf("%lu", &createTime[i]);
	}

	std::vector<std::set<UT>> itemLocs(K);
	std::vector<UT> itemLens(K);
	for (UT i = 0; i < K; i++) {
		scanf("%lu", &itemLens[i]);
	}

	for (UT i = 0; i < K; i++) {
		for (UT j = 0; j < itemLens[i]; j++) {
			UT x = 0;
			scanf("%lu", &x);
			itemLocs[i].insert(x-1);
		}
	}

	std::vector<std::vector<std::pair<UT, UT>>> G(N);
	for (UT i = 0; i < M; i++) {
		UT a, b, c;
		scanf("%lu %lu %lu", &a, &b, &c);

		G[a-1].emplace_back(b-1, c);
		G[b-1].emplace_back(a-1, c);
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

		/* printf("We are at node T=%lu K=%lu P=%lu\n", cur.time, cur.itemsDone, cur.position); */
		
		const auto& locs = itemLocs[cur.itemsDone];
		if (locs.count(cur.position)) {
			// we always skip if the items are in the current position.
			Q.emplace(cur.time, cur.itemsDone+1, cur.position);
		} else {
			// We consider crafting it ourselves.
			if (!seen.count({cur.itemsDone+1, cur.position})) {
				Q.emplace(cur.time + createTime[cur.itemsDone], cur.itemsDone+1, cur.position);
			}
			
			// We just add the nodes around us.
			for (const auto& [next, cost] : G[cur.position]) {
				if (!seen.count({cur.itemsDone, next}))
					Q.emplace(cur.time + cost, cur.itemsDone, next);
			}
		}
	}

	return 0;
}
