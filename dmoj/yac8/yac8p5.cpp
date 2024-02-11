/**
 * yac8p5 - Yet Another Contest 8 P5 - Hidden Tree
 *
 * This was a realllllllyyyyy cool task! It's basically a "run twice task",
 * meaning we control both the encoder and the decoder, but they share no other
 * state.
 *
 * I had to read the editorial here to get full marks here, but even then it took me
 * quite some time to implement it correctly.
 *
 * There are a couple of key ideas here, the first one being that since this is a tree,
 * if we chose a root for the tree, then we only need to store the (parent, depth) for
 * each node, to know where we need to go. If one node has a larger depth than the other,
 * it means we have to move towards the root to get to it. The only way we can do this, is
 * by moving to it's parent. Thus we know that the parent is in the path between them.
 *
 * We can encode this pair by doing MAX_N*depth + parent. Then it suffices to compare two
 * integers and choose the biggest one, since it will have the biggest depth. We can get the
 * parent of that integer by doing (combined % MAX_N), and we have our answer.
 *
 * It is clear that for our purposes then, the max integer in the output, scales with the
 * maximum depth of the rooted tree. This is worst in a line-graph, where we could potentially
 * get a max depth of 99, giving us 99XX something as the max value. From the problem statement,
 * we need the max value to be at most 2000.
 *
 * We can decrease this, by rooting the tree in the center of the graph. We can find this
 * either by simply running the "encoding" algorithm once for each vertex, using that vertex
 * as the root, and picking the output that has the smallest maximum element, or the more
 * elegant way, by finding the center and then running it once for that.
 *
 * In the case where there are 2 nodes that both are a center, we can simply use both with
 * depth 0. They will not be queried together and if nodes in different sides of the tree
 * are queried, they will have to go through one of them regardless. This brings the maximum
 * depth down to 50.
 *
 * This is where I ended up giving up and looking at the editorial.
 *
 * This brings the maximum depth down to 50. We can actually improve this further, by realizing
 * that by realizing that we are never comparing a node to it's parent or it's children. This
 * means they will never be compared, so we don't actually have to increments the child's value
 * over it's parent. It just have to be bigger than it's parents parent. It means that for the
 * current node cur we have:
 *
 * We will store parent[cur] for this node. In it's parent's parents node, we will store
 * parent[parent[parent[cur]]]. If we compare these two nodes then, we just need that
 *
 * depth[cur]*MAX_N + parent[cur] >= depth[parent[parent[cur]]]*MAX_N + parent[parent[parent[cur]]]
 *
 * We can assure this, by just setting depth[cur] = depth[parent[parent[cur]]] + 1. This means
 * we are only incrementing the depth of the nodes, every 2 levels, meaning we are storing
 * floor(depth/2) for each node. This brings the max depth down to 25, but we are still over
 * the 2000 limit.
 *
 * Ok, the above is fairly plain, and quite cool, but the next part is where it got REALLY interesting.
 * If we look a bit closer at the function above, we realize that there is another way to make
 * the inequality true, and that is if depth[cur] == depth[parent[parent[cur]]], but
 * parent[cur] >= parent[parent[parent[cur]]].
 *
 * This means that if we have a run of increasing parent values going down, we don't need to update
 * the depth, as when we are picking the bigger number in the decoding part of the scenario, we will
 * pick the child over the parent. It's not enough though, to just have the parent[parent[parent[cur]]]
 * be less, we need every parent above the current node, EXCEPT it's direct parent, with the same
 * depth as us, to be smaller than us. Otherwise, we could potentially query against a parent
 * longer up in the same chain, and it would pick the parent, instead of the child.
 *
 * This alone is enough to bring the average depth of all trees down significantly, but it's still
 * relatively easy to create trees where it will have the same max depth of 25. The last trick of the
 * puzzle, is to create a mapping function for the parent values, that distribute them randomly.
 * This doesn't improve the average depth of all trees, but it makes it close to impossible for the
 * grader to produce a test which produces a bad result.
 *
 * I generate the permutation by just shuffling an array of the numbers between 1 and MAX_N
 * and then producing a reverse mapping, for decoding. The shuffle is done with a fixed seed,
 * so the two runs of the program don't need to share any state.
 *
 * We then use this forwardMapping when testing the equality above and when encoding and the
 * reverseMapping when decoding.
 *
 * It took me really so much effort to implement this correctly. I didn't quite catch the fact
 * that the above inequality had to apply to all nodes of the same depth. I ended up writing
 * a test program, to try to figure out where I was getting the wrong answer. You can find
 * it in `yac8p5-interegator.py`, alongside this file.
 *
 * Even when I got an accepted solution, I didn't really understand why my previous attempts
 * didn't work. I asked on the discord and dug around and I couldn't figure out why some of
 * my solutions didn't find any problems locally, but when tested on the server, it produced
 * the wrong answer. In the end it turned out that my test program didn't check if the answer
 * given back was not the source or destination. Once I implemented that, suddenly I got wrong
 * cases immediately.
 *
 * The encoding is a little changed. We introduce a node 0, which is the parent node that all
 * roots of the tree have. As these roots should always be the smaller number, we always encode
 * them as 1. This means that we have to shift the output by +1, so that 0 becomes 1, 1 becomes 2
 * and so on. We adjust this back when decoding. It also means that we have to use MAX_N+1 as there
 * are 1 more element in the mix.
 *
 * I am not exactly sure why, but you don't actually need to test all the parents with the same
 * depth as you, it's enough to just check the two above the direct parent. I guess if they are less,
 * then all other above also have to be less. It doesn't really matter for our purposes, as N is
 * so small, but we implement the optimization regardless.
 *
 *
 * In finding the proper solution after the fact, I looked and learned at the
 * solution:
 *
 * https://dmoj.ca/src/6083492 by andrewtam
 *
 */
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <deque>
#include <random>
#include <unordered_set>

using UT = std::uint32_t;
using ST = std::int32_t;

constexpr UT MAX_N = 100;

using Graph = std::vector<std::unordered_set<UT>>;

// We are including a forward and backwards mapping, so that the
// chance of specificially crafted bad scenario goes down.
//
// While we are in the program, we don't operate with these,
// only when weighting the ods.
std::array<UT, MAX_N+1> forwardMapping;
std::array<UT, MAX_N+1> reverseMapping;
void initTreeMap() {
	forwardMapping[0] = 0;
	for (UT i = 1; i <= MAX_N; i++) {
		forwardMapping[i] = i;
	}
	
	std::mt19937 mt;
	mt.seed(400);

	// we are only shuffling from 1..N, the first element should always map to itself.
	std::shuffle(forwardMapping.begin()+1, forwardMapping.end(), mt);
	for (UT i = 0; i <= MAX_N; i++) {
		reverseMapping[forwardMapping[i]] = i;
	}
}

[[nodiscard]] UT encodePair(UT depth, UT parent) {
	return depth*(MAX_N+1) + parent + 1;
}

[[nodiscard]] UT decodePair(UT combined) {
	return (combined - 1) % (MAX_N+1);
}

void decode_mode() {
	UT Q = 0;
	scanf("%u", &Q);

	for (UT i = 0; i < Q; i++) {
		ST a = 0;
		ST b = 0;
		scanf("%u %u", &a, &b);

		if (a == -1 || b == -1)
			return;

		auto c = std::max(a, b);
		auto parent = decodePair(c);

		// We have to remember to map the reverse the parent mapping;
		printf("%u\n", reverseMapping[parent]);
		fflush(stdout);
	}
}

std::vector<UT> encode_graph(const Graph& G) {
	const UT N = G.size()-1;

	// First we are going to find the center. We are going to do that, by looking at
	// each layer and find the degree of each node. We are going to keep track of the
	// layer each node is on, so that later, we can start our iteration through the
	// tree, by looking at the start nodes.
	std::vector<UT> degree(N+1);
	std::vector<UT> layer(N+1);

	std::deque<UT> Q;
	for (UT i = 1; i <= N; i++) {
		degree[i] = G[i].size();
		if (degree[i] == 1) {
			layer[i] = 1;
			Q.push_back(i);
		}
	}

	// When the algorithm finishes, center will contain the index of one of the
	// top most nodes.
	UT center = 0;
	while (!Q.empty()) {
		center = Q.front();
		Q.pop_front();
		
		for (const auto v : G[center]) {
			// We now remove the connection between them.
			degree[v]--;

			if (degree[v] == 1) {
				// This node now only have 1 other connection remaining,
				// so we add it to the next line of items we are going
				// to be looking at.
				layer[v] = layer[center] + 1;
				Q.push_back(v);
			}
		}
	}

	std::vector<UT> depth(N+1, N+2);
	std::vector<UT> parent(N+1);

	for (UT i = 1; i <= N; i++) {
		if (layer[i] == layer[center]) {
			depth[i] = 0;
			parent[i] = 0;
			Q.push_back(i);
		}
	}

	// Now the Q is filled with with the other nodes that share the same priorty.
	// This should be at most 2, and at least 1.
	while (!Q.empty()) {
		UT cur = Q.front();
		Q.pop_front();

		for (const auto next : G[cur]) {
			if (depth[next] != N+2)
				continue;

			parent[next] = cur;
			// The depth will be at least as much as our current depth.
			depth[next] = depth[cur];
			
			// We just need to check 2 levels here, as anything beyond that must
			// already be sorted
			auto cur_p = parent[cur];
			UT count = 0;
			while (count < 2 && cur_p != 0 && depth[next] == depth[cur_p]) {
				if (forwardMapping[cur] < forwardMapping[parent[cur_p]]) {
					depth[next] += 1;
					break;
				}

				cur_p = parent[cur_p];
				count++;
			}
			// Now we got to look at the stack going up.
			Q.push_back(next);
		}
	}

	
	// Now we have the depths and the parents values, so we now create the output
	std::vector<UT> ans(N);
	for (UT i = 0; i < N; i++) {
		ans[i] = encodePair(depth[i+1], forwardMapping[parent[i+1]]);
	}

	return ans;
}

void encode_mode() {
	// ok we are going to read in the graph now
	UT N = 0;
	scanf("%u", &N);

	Graph G(N+1);
	for (UT i = 0; i < N-1; i++) {
		ST a = 0;
		ST b = 0;
		scanf("%u %u", &a, &b);
	
		G[a].insert(b);
		G[b].insert(a);
	}

	auto output = encode_graph(G);
	// We need to add 1 to the output, as we are operating shifted by 1 to make the math
	// easier in the main program.
	for (const auto &v : output)
		printf("%u ", v);

	printf("\n");
}

int main() {
	initTreeMap();

	UT mode = 0;
	scanf("%u", &mode);

	if (mode == 1) {
		encode_mode();

	} else if (mode == 2) {
		decode_mode();
	}
	return 0;
}
