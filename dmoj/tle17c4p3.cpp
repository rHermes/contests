/**
 * tle17c4p3 - TLE '17 Contest 4 P3 - Fax's Christmas Dish
 *
 * This becomes a simple directed graph problem, where we
 * just update the elements upwards as we go, and stop when
 * -1 is done.
 */

#include <cstdio>
#include <cstdint>

#include <array>

using ST = std::int32_t;
using UT = std::uint32_t;

constexpr UT MAX_N = 300000 + 1;

struct Node {
	// -1 if no parents are here.
	ST parent{-1};

	bool done{false};

	// How many requirements do I have?
	UT children{0};
};

std::array<Node, MAX_N> NODES;

void update_nodes(const UT id) {
	auto& node = NODES[id];

	if (node.done)
		return;

	node.done = true;

	// Now we get to update upwards,
	if (node.parent == -1 && !NODES[node.parent].done)
		return;

	NODES[node.parent].children--;
	if (NODES[node.parent].children == 0) {
		update_nodes(node.parent);
	}
}

int main(void) {
	UT N, M, D;
	scanf("%u %u %u", &N, &M, &D);

	for (UT i = 0; i < M; i++) {
		UT target, needed;
		scanf("%u %u", &target, &needed);

		NODES[target].children = needed;

		for (UT j = 0; j < needed; j++) {
			UT id;
			scanf("%u", &id);
			NODES[id].parent = target;
		}
	}

	// Now we reading in them days
	UT day = 0;
	for (; day < D; day++) {
		if (NODES[1].done) {
			break;
		}

		UT p;
		scanf("%u", &p);
		update_nodes(p);
	}

	if (NODES[1].done)
			printf("%u\n", day);
	else 
		printf("-1\n");

	return 0;
}
