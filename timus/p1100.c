/*
 * p1100 - Final Standings
 *
 * Any stable sort will do here. Since we have a very limited space that we 
 * are solving over, 0 <= M <= 100, we can use a counting sort, to do this
 * faster. It isn't really all that faster though, but it's cool, so I'll
 * stick with it.
 */
#include <stdio.h>
#include <inttypes.h>

#define MAXM 101
#define MAXN 150000

// Use bitfield here, to save some space.
typedef struct {
	uint32_t id  : 24;
	uint8_t solved :  8;
} pair;

uint32_t count[MAXM] = {0};
pair teams[MAXN];
pair extra[MAXN];

int main() {
	uint32_t N, ID, M, i;
	scanf("%"SCNu32, &N);
	for (i = 0; i < N; i++) {
		scanf("%" SCNu32 " %" SCNu32, &ID, &M);
		teams[i].id = ID;
		teams[i].solved = MAXM-1-M;

		count[MAXM-1-M]++;
	}

	uint32_t total = 0;
	uint32_t oldCount = 0;
	for (i = 0; i < MAXM; i++) {
		oldCount = count[i];
		count[i] = total;
		total += oldCount;
	}

	for (i = 0; i < N; i++) {
		extra[count[teams[i].solved]] = teams[i];
		count[teams[i].solved]++;
	}

	// Now the list is sorted, we print them out.
	for (i = 0; i < N; i++) {
		printf("%" PRIu32 " %" PRIu8 "\n", extra[i].id, MAXM-1-extra[i].solved);
	}
	return 0;
}

