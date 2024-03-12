#include <iostream>
#include <map>
#include <limits>
#include <set>
#include <vector>
#include <cinttypes>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <deque>

using UT = std::uint64_t;
using ST = std::int64_t;

void solve() {
	UT N = 0;
	UT M = 0;
	std::cin >> N >> M;

	// There can be a maximum of N nodes and M unique colors
	std::vector<std::vector<UT>> edges(N+M);
	std::unordered_map<UT,UT> compression;
	for (UT i = 0; i < M; i++) {
		UT u = 0;
		UT v = 0;
		UT c = 0;

		std::cin >> u >> v >> c;
		u--;
		v--;
		
		// we compress the edge color.
		auto inst = compression.emplace(c, N + compression.size());
		auto idx =  inst.first->second;
		
		// This could potentially create a lot of duplication, but we are willing to live with that.
		edges[u].emplace_back(idx);
		edges[v].emplace_back(idx);

		edges[idx].emplace_back(u);
		edges[idx].emplace_back(v);
	}


	UT srcNode = 0;
	UT dstNode = 0;
	std::cin >> srcNode >> dstNode;
	srcNode--;
	dstNode--;
	
	std::unordered_map<UT,UT> depth;
	depth[srcNode] = 0;

	std::deque<UT> Q;
	Q.emplace_back(srcNode);
	while (!Q.empty()) {
		const auto cur = Q.front();
		Q.pop_front();

		if (cur == dstNode) {
			std::cout << depth[cur] << std::endl;
			return;
		}
	
		// We deduplicate here, to avoid more lookups in the inner loop.
		// We don't bother to erase, as we will never see this node again.
		auto& nexts = edges[cur];
		std::sort(nexts.begin(), nexts.end());
		const auto end = std::unique(nexts.begin(), nexts.end());

		for (auto it = nexts.begin(); it != end; ++it) {
			if (depth.count(*it))
				continue;

			Q.emplace_back(*it);
			// If we are visiting a color node, we increase the depth.
			depth[*it] = depth[cur] + (N <= *it);
		}
	}

	std::cout << "This is not meant to happen!" << std::endl;
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
