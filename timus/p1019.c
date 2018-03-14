/*
 * p. 1019 - Line Painting
 *
 * This seems to be something one could solve with a simple
 * linked list.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAXB 1000000000
#define MAXN 5000

typedef struct mark {
	struct mark *prev;
	struct mark *next;

	bool white;
	int start;
	int length;
} mark;


void repaint(mark **root, mark *new) {

}

int main() {
	// Set up the painting.
	mark marks[MAXN];

	// we init the first one.
	mark *root = marks;
	root->prev = NULL;
	root->next = NULL;
	root->white = true;
	root->start = 0;
	root->length = MAXB;
#ifdef ONLINE_JUDGE

#else
	//int N = 4;
	marks[1].white = false;
	marks[1].start = 1;
	marks[1].length
	repaint(&)

#endif

}
