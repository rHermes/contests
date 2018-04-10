/*
 * p1037 - Memory Management
 *
 * We start with the dumb way and then fix it later.
 *
 * Important to note is that it is 10 minutes, not seconds.
 */

#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 30000
#define T 600

int_fast32_t G[N];

char buff[128];

int main() {
	uint_fast16_t time_cur;
	uint_fast16_t block_no;
	// We set them to -11, because then, we are sure that if they haven't been
	// allocated, they will be when we test against them.
	
	memset(G, -(T + 1), sizeof(G));
	// Init before entering loop.
	fgets(buff, sizeof(buff), stdin);

	while(!feof(stdin)) {
		char *tmp;
		time_cur = strtoul(buff, &tmp, 10);
		
		// Get rid of spaces.
		while(isspace(*tmp)) {
			tmp++;
		}

		// either we have a + or a .
		if (*tmp == '+') {
			block_no = 0;
			// we are requesting a block.
			while (time_cur - G[block_no++] < T) { }

			// block_no is now the output and block_no-1 must be set to T
			printf("%" PRIuFAST16 "\n", block_no);

			G[block_no-1] = time_cur;
		} else {
			// We are requesting access.
			block_no = strtoul(++tmp, NULL, 10);
			block_no--;

			if (time_cur - G[block_no] < T) {
				// We are good.
				G[block_no] = time_cur;
				printf("+\n");
			} else {
				printf("-\n");
			}
		}

		// Update the buffer.
		fgets(buff, sizeof(buff), stdin);
	}
	return 0;
}
