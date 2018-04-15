/*
 * p1039 - Anniversary Party
 *
 * I assume here that the 
 *
 * Build tree, calculate height, sort by height, do dp upwards, print result.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 6000

#define max(x,y) ( \
    { __auto_type __x = (x); __auto_type __y = (y); \
      __x > __y ? __x : __y; })

typedef struct SNode {
	int height;

	int invite;
	int ignore;

	struct SNode *parent;
} Node;

// this calculates the height of the node.
int calc_height(Node *r) {
	if (r->height) {
		return r->height;
	}

	if (r->parent == NULL) {
		r->height = 1;
		return 1;
	} 

	r->height = 1 + calc_height(r->parent);
	return r->height;
}

Node tree[MAX_N];
Node *sort_tree[MAX_N];
Node *sort_tree_2[MAX_N];

void top_down_merge(Node **A, int begin, int middle, int end, Node **B) {
	int i, j, k;

	i = begin;
	j = middle;
	for (k = begin; k < end; k++) {
		if (i < middle && (j >= end || (A[i]->height >= A[j]->height))) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}	
	}
}

void top_down_split_merge(Node **B, int begin, int end, Node **A) {
	if (end - begin < 2) {
		return;
	}
	int middle = (end+begin)/2;
	top_down_split_merge(A, begin, middle, B);
	top_down_split_merge(A, middle, end, B);

	top_down_merge(B, begin, middle, end, A);
}

char buff[32];
int main() {
	fgets(buff, sizeof(buff), stdin);
	int n = strtol(buff, NULL, 10);

	for (int i = 0; i < n; i++) {
		fgets(buff, sizeof(buff), stdin);

		// We eliminate less than 0 here, because it leads to simpler code later.
		short lol = strtol(buff, NULL, 10);
		lol = lol > 0 ? lol : 0;
		tree[i].invite = lol;
		tree[i].parent = NULL;

		sort_tree[i] = tree + i;
		sort_tree_2[i] = tree + i;
	}

	// Special case where there are only 1 or 2 employees?

	while (fgets(buff, sizeof(buff), stdin) != NULL) {
		char *tmp = buff;
		int l = strtol(tmp, &tmp, 10);
		int k = strtol(tmp, &tmp, 10);

		if (l == 0 && k == 0) {
			break;
		}

		tree[l-1].parent = tree + k - 1;
	}

	// Figure out the heights of the various members.
	for (int i = 0; i < n; i++) {
		calc_height(tree + i);
	}

	// Sort my array.
	// I don't know the running time of qsort, so I use my own sort.
	// qsort(sort_tree, n, sizeof(sort_tree[0]), cmpNodeP);
	// Sort array with a merge sort.
	top_down_split_merge(sort_tree_2, 0, n, sort_tree);


	// Now we build up the DP.
	// if the parent is NULL, we have to add the sum to the total answer.
	int ans = 0; 
	for (int i = 0; i < n; i++) {
		Node k = *(sort_tree[i]);
		if (k.parent != NULL) {
			k.parent->invite += k.ignore;
			k.parent->ignore += max(k.ignore, k.invite);
		} else {
			ans += max(k.ignore, k.invite);
		}
	}

	// Now the last one is just the max of k.invite or k.ignore.
	printf("%d\n", ans);

	return 0;
}
