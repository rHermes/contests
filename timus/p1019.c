/*
 * p. 1019 - Line Painting
 *
 * This seems to be something one could solve with a simple
 * linked list.
 *
 *
 * important to note here that the intervals are all of the form [a, b),
 * even the output.
 *
 * This turned out to be a real messy implementation, since there are so many
 * edge cases. The important thing to remember though, is that we are simply
 * keeping a list of the elements in memory and an invariant of that list is
 * that no two elements on either side, should have the same color.
 *
 * This could have been done in a two stage process, where the first step was
 * the insertion and freeing of elements if there where any between the two,
 * and then a second stage where you merged things with equal color and freed
 * intervals with 0 length, but this would have been less effective overall.
 *
 * it doesn't really matter, but since I started down this road, I'm going to
 * finish it.
 * 
 * For completly optimal performance, I could have used a pool for the allocated
 * values, but this would have been a total overkill.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MAXB 1000000000
#define MAXN 5000

typedef struct mark {
	struct mark *prev;
	struct mark *next;

	bool white;

	// This interval is [start, end)
	int start;
	int end;
} mark;


void repaint(mark *root, int a, int b, bool c) {
	// First we find the first mark that contains the others end.
	mark *iter = root;

	// we find the left edge
	while (iter->end <= a) {
		iter = iter->next;
	}
	mark *left_edge = iter;
	
	// we find the right edge.
	while (iter->end < b) {
		iter = iter->next;
	}
	mark *right_edge = iter;

	bool on_left = left_edge->start == a;
	bool on_right = right_edge->end == b;

	// Ok, so now there are 2 possibilities, they either have the same color or they don't.
	if (left_edge == right_edge) {
		// If we are the same color as the thingy we are trying to change,
		// we don't do anything. We are contained within it and it doesn't really
		// matter if we change color
		if (left_edge->white == c) {
			return;
		}

		if (on_left && on_right) {
			// it's exactly the same as the the we are on.
			// What we will do is simply free this and the next, and just
			// extend the one to the left of this.
			
			// we simply extend the one to the left, and then we have to free the two other ones.
			left_edge->prev->end = left_edge->next->end;
			left_edge->prev->next = left_edge->next->next;

			if (left_edge->next->next != NULL) {
				left_edge->next->next->prev = left_edge->prev;
			}

			free(left_edge->next);
			free(left_edge);
		} else if (on_left) {
			// if it's the same on the left we simply extend the previous one and
			// shrink this.
			left_edge->start = b;
			left_edge->prev->end = b;
		} else if (on_right) {
			// if it's the same on the right we simply extend the rigth one and insert.
			left_edge->end = a;
			left_edge->next->start = a;
		} else {
			// we are completly contained within this.
			// if not we simply have to insert 2 new markers.
			mark* l = malloc(sizeof(mark));
			mark* r = malloc(sizeof(mark));

			l->prev = left_edge;
			l->next = r;
			l->start = a;
			l->end = b;
			l->white = c;

			r->prev = l;
			r->next = left_edge->next;
			r->start = b;
			r->white = left_edge->white;
			r->end = left_edge->end;

			// Now we simply insert it into the linked list.
			if (left_edge->next != NULL) {
				left_edge->next->prev = r;
			}
			left_edge->next = l;
			left_edge->end = a;

		}
	} else {
		// We are spanning more than one range.
		//
		// First we can free any edge between the two of these we aren't going to be using them.
		mark *iter = left_edge->next;
		while (iter != right_edge) {
			mark *tmp = iter->next;
			free(iter);
			iter = tmp;
		}
		left_edge->next = right_edge;
		right_edge->prev = left_edge;

		// Lets just combine the two.
		if (left_edge->white == right_edge->white) {
			// If this is the same as the new one, we simply,
			// merge the two and free the right edge.
			if (left_edge->white == c) {
				left_edge->next = right_edge->next;
				left_edge->end = right_edge->end;
				if (right_edge->next) {
					right_edge->next->prev = left_edge;
				}
				free(right_edge);
			} else {
				// They are both the "wrong" color, so we must allocate at most one.
				// If we are completly contained in it.

				// if it is equal to the one on the left, we simply remove the left_edge
				if (on_left && on_right) {
					// If this happens, we delete the one on the left and right, since
					// they will be swallowed by the two on the sides.
					
					left_edge->prev->end = right_edge->next->end;
					left_edge->prev->next = right_edge->next->next;
					if (right_edge->next->next) {
						right_edge->next->next->prev = left_edge->prev;
					}

					free(left_edge);
					free(right_edge->next);
					free(right_edge);
				} else if (on_left) {
					// The one on the left gets swallowed
					left_edge->prev->next = right_edge;
					left_edge->prev->end = b;
					right_edge->start = b;
					right_edge->prev = left_edge->prev;
					free(left_edge);
				} else if (on_right) {
				// The one on the right gets swallowed
					left_edge->end = a;
					right_edge->next->start = a;

					left_edge->next = right_edge->next;
					right_edge->next->prev = left_edge;
					free(right_edge);
				} else {
					// It is totally contained between the two trees, and all we need to do
					// is create one.
					mark *new = malloc(sizeof(mark));

					// Setup new 
					new->prev = left_edge;
					new->next = right_edge;
					new->start = a;
					new->end = b;
					new->white = c;

					
					// Update the left and right edges.
					left_edge->end = a;
					right_edge->start = b;

					right_edge->prev = new;
					left_edge->next = new;
				}
			}
		} else {
			// One of them is the "wrong" color, and so we will not get this 
			if (left_edge->white == c) {
				// The left_edge has the right color.
				// Two possibilites:
				//
				// either b is on the end of right_edge or it is not.
				// if it is , we have to delete right_edge, if it isn't,
				// we simply resize.
				if (on_right) {

					left_edge->end = right_edge->next->end;
					left_edge->next = right_edge->next->next;

					if (right_edge->next->next) {
						right_edge->next->next->prev = left_edge;
					}

					free(right_edge->next);
					free(right_edge);
				} else {
					// We simply resize.
					left_edge->end = b;
					right_edge->start = b;
				}
			} else {
				// this means that the right side is correct.
				// Same as above.
				if (on_left) {
					right_edge->start = left_edge->prev->start;
					right_edge->prev = left_edge->prev->prev;

					if (left_edge->prev->prev) {
						left_edge->prev->prev->next = right_edge;
					}

					free(left_edge->prev);
					free(left_edge);
				} else {
					// Otherwise, we simply resize.
					left_edge->end = a;
					right_edge->start = a;
				}
			}
		}
	}
}

int main() {
	// we init the first one.
	mark *root = malloc(sizeof(*root));
	root->prev = NULL;
	root->next = NULL;
	root->white = true;
	root->start = 0;
	root->end = MAXB;

	int N = 0;
	scanf("%d\n", &N);

	for (int i = 0; i < N; i++) {
		char c;
		int a, b;
		scanf("%d %d %c\n", &a, &b, &c);
		repaint(root, a, b, c == 'w');
	}

	// we now have a nice root, which we can just iterate over and keep the longest sequence in mind.
	mark *max = root;
	mark *iter = root->next;
	while (iter != NULL) {
		mark *tmp = iter->next;
		if (iter->white && (max->end - max->start < iter->end - iter->start)) {
			free(max);
			max = iter;
		} else {
			free(iter);
		}
		iter = tmp;
	}

	// Print out our answer.
	printf("%d %d\n", max->start, max->end);
	free(max);
	
	return 0;
}
