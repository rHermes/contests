/*
 * p1018 - Binary Apple Tree
 *
 * This seems to be solved with dynamic programming of
 * some kind.
 *
 * One thing to note is that the tree is a proper binary tree,
 * meaning that each node either has 0 or 2 children.
 *
 *
 * What I have now is a bruteforce solution, but it is not fast enough.
 * I am looking for ways to make this faster.
 *
 * Memorisation was enoughy to get this to work.
 *
 */

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#define MAXN 100

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


struct Node {
	uint16_t id;
	uint16_t l_cost;
	uint16_t r_cost;

	struct Node *l;
	struct Node *r;
};

// This is silly, but it is the way it is.
struct Node nodes[MAXN+1];

// We now try to see how many hits we get.
int64_t memo[MAXN+1][MAXN];

// If we return negative, then there is no way to do that.
int64_t F(struct Node *root, uint16_t left) {
	// The answer we get is ans + 1, so that we know that we have calculated it
	// even if the answer is 0.
	if (memo[root->id][left] > 0) {
		return memo[root->id][left]-1;
	}

	// We check if we have chilren
	bool parent = root->l != NULL;
	if (left == 0) {
		memo[root->id][left] = 1;
		return 0;
	} 
	if (left == 1) {
		int64_t ans = max(root->l_cost, root->r_cost);
		memo[root->id][left] = ans+1;
		return ans;
	}
	// We get it here too.
	// here left is 2 or more. This means that we must
	// have atleast one branch.
	if (parent) {
		int64_t r_f = F(root->r, left-1);
		int64_t l_f = F(root->l, left-1);

		int64_t maxans = max(root->r_cost + r_f, root->l_cost + l_f);

		// ok, so now that we got a baseline, we have to consider all the possible distrubitions
		// between the two trees.
		for (int i = 0; i <= left-2; i++) {
			int64_t rlr_f = F(root->r, i);
			int64_t rll_f = F(root->l, (left-2-i));
			if ((root->r_cost + root->l_cost + rlr_f + rll_f) > maxans) {
				maxans = root->r_cost + root->l_cost + rlr_f + rll_f;
			}

		}

		memo[root->id][left] = maxans + 1;

		// Now we must just see if any of these, work.
		return maxans;
	}

	memo[root->id][left] = 1;
	return 0;
}

// Just to make this easier.
void set_node(struct Node *c, int a, int b, uint16_t lc, uint16_t rc ) {
	c->l = nodes + a;
	c->r = nodes + b;
	c->l_cost = lc;
	c->r_cost = rc;
}

// This is the adjenecy matrix.
uint16_t GG[MAXN+1][MAXN+1];

void build_nodes(uint16_t idx, uint16_t N) {
	struct Node *c = nodes + idx;
	uint16_t l = 0;
	uint16_t r = 0;

	uint16_t *G = GG[idx];

	for (int i = 1; i <= N; i++) {
		if (G[i] > 0) {
			if (l) {
				r = i;
				break;
			}
			l = i;
		}
	}
	
	// we are a child node, so no need to do anything.
	if (l == 0) {
		return;
	}

	// Set those two to 0 after wards.
	set_node(c, l, r, G[l]-1, G[r]-1);

	// Set the two to 0 after wards.
	GG[idx][l] = GG[l][idx] = 0;
	GG[idx][r] = GG[r][idx] = 0;

	// Now set those two.
	build_nodes(l, N);
	build_nodes(r, N);
}

// Ok, so to build the tree, we can use a graph, I'll just test my algo for now.
int main() {
	// Now we just scan in the nodes.
	uint16_t N, Q;

	// We init the memory for the memorization
	scanf("%" SCNu16 " %" SCNu16, &N, &Q); // NOLINT

	// init the nodes.
	for (int i = 1; i <= N; i++) {
		struct Node *c = nodes + i;

		c->id = i;

		c->l = NULL;
		c->l_cost = 0;

		c->r = NULL;
		c->r_cost = 0;
	}


	// Now we have to read in the numbers and the number of branches.
	for (int i = 0; i < N-1; i++) {
		uint16_t a, b, c;
		scanf("%" SCNu16 " %" SCNu16 " %" SCNu16, &a, &b, &c); // NOLINT
		
		// This is +1, so that even if we get 0, we know that the place was set.
		GG[a][b] = GG[b][a] = c+1;
	}

	// Now we need to build the nodes. 
	build_nodes(1,N);
	
	printf("%" PRId64 "\n", F(nodes+1, Q));

	return 0;
}
