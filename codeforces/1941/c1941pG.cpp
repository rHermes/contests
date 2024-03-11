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

	// node -> lines
	std::map<UT,std::unordered_set<UT>> nodes;
	// all nodes in a line.
	std::map<UT,std::unordered_set<UT>> lines;

	for (UT i = 0; i < M; i++) {
		UT u = 0;
		UT v = 0;
		UT c = 0;

		std::cin >> u >> v >> c;
		nodes[u].emplace(c);
		nodes[v].emplace(c);
		auto& line = lines[c];
		line.emplace(u);
		line.emplace(v);
	}

	UT srcNode = 0;
	UT dstNode = 0;
	std::cin >> srcNode >> dstNode;
	
	std::set<UT> linesSeen;
	std::set<UT> nodesSeen;
	std::deque<std::pair<UT,UT>> Q;
	Q.emplace_back(srcNode, 0);

	while (!Q.empty()) {
		const auto [cur, numLines] = Q.front();
		Q.pop_front();

		if (cur == dstNode) {
			std::cout << numLines << std::endl;
			return;
		}

		if (auto inst = nodesSeen.emplace(cur); !inst.second)
			continue;

		for (const auto& line : nodes[cur]) {
			if (auto inst = linesSeen.emplace(line); !inst.second)
				continue;

			// we just add any node here, it will be too slow, but we will skip the lines once we get there.
			for (const auto& next : lines[line]) {
				if (nodesSeen.count(next))
					continue;

				Q.emplace_back(next, numLines+1);
			}
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
		/* break; */
	}
}
