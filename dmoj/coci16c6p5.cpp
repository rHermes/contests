/**
 * coci16c6p5 - COCI '16 Contest 6 #5 Sirni
 *
 * This has something to do with sets I think?
 *
 */

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cinttypes>
#include <limits>
#include <set>
#include <iterator>
#include <tuple>
#include <utility>

std::vector<uint32_t> read_input() {
	uint32_t N;
	scanf("%" SCNu32, &N);

	std::vector<uint32_t> ins;

	for (uint32_t i = 0; i < N; i++) {
		uint32_t in;
		scanf("%" SCNu32, &in);
		ins.push_back(in);
	}
	
	return ins;
}

// Solve this using a minimal spanning tree
uint32_t solve_with_mst(std::vector<uint32_t> input) {
	// Special case if we only have one
	if (input.size() < 2) {
		return 0;
	}


	std::set<std::pair<uint32_t,uint32_t>> Q;
	for (const auto d : input) {
		Q.insert(std::make_pair(std::numeric_limits<uint32_t>::max(),d));
	}

	// printf("%ld\n", Q.size());

	bool first = true;
	// the accumulator for the answer
	uint32_t ans = 0;
	while (!Q.empty()) {
		const auto elem = Q.extract(Q.begin());
	
		// cheat on the first one and set it to 0
		if (first) {
			elem.value().first = 0;
			first = false;
		}

		const auto [cost, node] = elem.value();
		// printf("Node: %u, Cost: %u, Total: %u\n", node, cost, ans);

		// Now we must update the other weights
		
		auto cur = Q.begin();
		while (cur != Q.end()) {
			const auto [acost, bnode] = *cur;
			cur++;
		
			// New cost
			const auto newcost = std::max(node,bnode) % std::min(node,bnode);

			if (newcost < acost) {
				auto aanode = Q.extract(std::prev(cur,1));
				aanode.value().first = newcost;
				Q.insert(std::move(aanode));
			}
		}

	
		// The answer is the cost 
		ans += cost;
	}


	return ans;
}


int main() {
	auto ins = read_input();

	auto ans = solve_with_mst(ins);

	// printf("mst: %" PRIu32 "\n", ans);
	printf("%" PRIu32 "\n", ans);

	return 0;
}
