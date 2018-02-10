// Holes problem.
//
//
// This can be done with dynamic programming. We just keep track of where we
// are going to end up on each step.

#include <stdio.h>
#include <stdlib.h>

struct s_hole {
	char dirty;
	int jumps;
	int last;
	int power;
};

struct s_prob {
	int N;
	int M;
	struct s_hole *holes;
};


// THis update always goes right.
void update(int i, int N, struct s_hole *holes) {
	struct s_hole *hole = holes + i;
	
	// If this hole isn't dirty, we simply don't do anything.
	if (!hole->dirty) {
		return;
	}

	int next = hole->power + i;

	if (next >= N) {
		hole->jumps = 1;
		hole->last = i;
	}  else {
		// Update the next in line.
		update(next, N, holes);
		hole->jumps = 1 + holes[next].jumps;
		hole->last = holes[next].last;
	}
	hole->dirty = 0;
}

int main() {
	// First read in the answer.
	int N, M;

	int rc = scanf("%d %d", &N, &M);
	if (rc != 2) {
		printf("ONLY GOT ONE!\n");
		return -1;
	}

	// we now allocate the values.
	struct s_hole *holes = malloc(N*sizeof(struct s_hole));
	if (holes == NULL) {
		printf("MALLOC FAILURE!\n");
		return -1;
	}

	// Now we loop through the initial values.
	for (int i = 0; i < N; i++) {
		holes[i].dirty = 1;
		int powr = 0;
		if (scanf("%d", &powr) != 1) {
			printf("ERROR READING IN!\n");
			return -1;
		}
		holes[i].power = powr;
	}

	// Now we loop through the moves
	int des = 0, a = 0, b = 0;
	int last_dirty = -1;
	for (int i = 0; i < M; i++) {
		if (scanf("%d %d", &des, &a) != 2) {
			printf("ERROR READING IN!\n");
			return -1;
		}

		if (des == 0) {
			if(scanf("%d", &b) != 1) {
				printf("ERROR READING IN!\n");
				return -1;
			}
			
			if (last_dirty < a) {
				last_dirty = a;
			}
			(holes + (a-1))->power = b;
		} else {
			if (last_dirty > 0) {
				for (int j = 0; j < last_dirty; j++) {
					(holes + j)->dirty = 1;
				}
				last_dirty = -1;
			}
			// First we just update that hole.
			update(a-1, N, holes);
			printf("%d %d\n", holes[a-1].last + 1, holes[a-1].jumps);
		}
	}
	
	// we must free the holes info.
	free(holes);

	return 0;
}
