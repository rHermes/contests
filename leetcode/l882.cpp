#include <vector>
#include <queue>

class Solution {
public:
	int reachableNodes(std::vector<std::vector<int>>& edges, int maxMoves, int n) {
		std::vector<std::vector<std::pair<std::size_t, int>>> G(n);

		for (const auto& edge : edges) {
			G[edge[0]].emplace_back(edge[1], edge[2]);
			G[edge[1]].emplace_back(edge[0], edge[2]);
		}

		// ok, so here is the problem: This would be a super simple
		// task, if it wasn't for the fact that we can approach some
		// of these edges from both ways. Instead of handling this
		// problem head on, we just do one pass where we find all
		// reachable edges and then another where we sum the number
		// of edges up.

		// moves left, current node, in the original.
		using NodeType = std::pair<int, std::size_t>;
		// How much distance we have left when we reach the original node.
		std::vector<int> distLeft(n, -1);
		distLeft[0] = maxMoves;


		int answer = 0;

		std::priority_queue<NodeType> Q;
		Q.emplace(maxMoves, 0);

		while (!Q.empty()) {
			const auto [curLeft, curNode] = Q.top();
			Q.pop();

			if (curLeft < distLeft[curNode])
				continue;

			answer++;

			for (const auto& [nextNode, cost] : G[curNode]) {
				const auto realCost = cost + 1;
				if (distLeft[nextNode] < (curLeft - realCost)) {
					distLeft[nextNode] = curLeft - realCost;
					Q.emplace(curLeft - realCost, nextNode);
				}   
			}
		}

		// now I want to add the edges between.
		for (const auto& edge : edges) {
			auto aLeft = std::max(distLeft[edge[0]], 0);
			auto bLeft = std::max(distLeft[edge[1]], 0);

			const auto splits = edge[2];

			// ok, the number of nodes we will be able to take is max splits
			answer += std::min(splits, (aLeft + bLeft));
		}

		return answer;
	}
};

int main() { return 0;}
