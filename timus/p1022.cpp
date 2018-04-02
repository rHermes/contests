/*
 * p1022 - Genealogical Tree
 *
 * To solve this one simply does a topological sort.
 * This requires a simple algorithm.
 */
#include <cstdio>

#include <vector>
#include <queue>
#include <set>

class Node {
	public:
		int ID;
		std::set<Node*> edges;
		int in_edges;

		Node() : ID(0), in_edges(0) {}
		Node(int id) : ID(id), in_edges(0) {}
};

int main() {
	int N;
	std::scanf("%d", &N);

	std::vector<Node> nodes(N);
	for (int i = 0; i < N; i++) {
		Node* nn = &nodes[i];
		
		// Set the id.
		nn->ID = i+1;

		int a;
		std::scanf("%d" , &a);
		while (a) {
			Node* na = &nodes[a-1];
			na->in_edges++;
			nn->edges.insert(na);

			std::scanf("%d" , &a);
		}
	}

	std::vector<int> L;
	std::queue<Node*> Q;

	for (int i = 0; i < N; i++) {
		Node* na = &nodes[i];
		if (!na->in_edges) {
			Q.emplace(na);
		}
	}

	// Now we have the queue, and so we can go through the queue.
	while (!Q.empty()) {
		Node* nn = Q.front();
		Q.pop();
		
		L.emplace_back(nn->ID);

		for (auto& na : nn->edges ) {
			na->in_edges--;

			if (na->in_edges == 0) {
				Q.emplace(na);
			}
		}
	}

	for (auto& n : L) {
		std::printf("%d ", n);
	}
	std::printf("\n");
	return 0;
}
