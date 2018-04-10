/*
 * p1028 - Stars
 *
 * This might done with some kind of partial sum?
 *
 * f(x,y) = s(x,y) + s(x,y-1) + s(x,y - 1) ..
 *
 * Where S(y) is the amount of stars. We could also create a graph from this
 * and do longest possible way? This would not work however. What one would
 * have to do is to record the number of total stars you can accumulate to
 * a certain node and this is expensive.
 *
 * The time limit is low however, so maybe this isn't the way?
 *
 * Another way to do this is to have sort of data structure where I can query
 * for number of points less than a certain X address. After star is considered,
 * I add it to this datastructure, and then continue. This would always be correct,
 * since the stars are listed in such an acending ordered.
 *
 * There are multiple ways of solving this. One of them is an Binary Index Tree,
 * where you shift the X by +1, to avoid the = case.
 *
 *
 * Another is to divide the distances up into sectors, n = 128. Then 
 * level = sector[x/250]+ Xpivot[i] that i=int(x/250)*250 to x
 *
 * And you update the value of all sectors greater than this sector.
 *
 * https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/
 * https://cs.stackexchange.com/questions/10538/bit-what-is-the-intuition-behind-a-binary-indexed-tree-and-how-was-it-thought-a
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 15005
#define MAX_XY 32005

// This gives you the least significant bit.
#define BLSI(i) ((i) & -(i))

char buff[64];
int tree[MAX_XY] = {0};
int level[MAX_N] = {0};

int main() {
	int N;
	// Read in the buffer.
	fgets(buff, sizeof(buff), stdin);
	N = strtol(buff, NULL, 10);

	for (int i = 0; i < N; i++) {
		fgets(buff, sizeof(buff), stdin);
		unsigned x = strtol(buff, NULL, 10);
		// we must do this to avoid the 0 case.
		x++;

		// I've inlined the binary index tree here.
		unsigned i = x;
		unsigned sum = 0;

		while (i > 0) {
			sum += tree[i];
			i -= BLSI(i); 
		}
		
		// Increment the level.
		level[sum]++;

		while (x <= MAX_XY) {
			tree[x]++;
			x += BLSI(x);
		}
	}

	for (int i = 0; i < N; i++) {
		printf("%d\n", level[i]);
	}

	return 0;
}
