/*
 * Texture Analysis
 *
 * This is not as fast as it could be, I wonder if it would be possble to 
 * build a string in memory and then do a single compare, but I'm not sure.
 */

#include <stdio.h>
#include <string.h>

#define MAXN 1000

int main(void) {
	char buff[MAXN+1];
	for (int i = 1; i <= 2001; i++) {
		scanf("%s", buff);
		if (strncmp("END", buff, 4) == 0) {
			break;
		}

		size_t l = strnlen(buff, MAXN);
		size_t gap;
		for (gap = 1; gap < l && buff[gap] == '.'; gap++) {}
		
		printf("%d ", i);
		for (size_t j = 0; j < l; j++) {
			if ((j % gap == 0) ^ (buff[j] == '*')) {
				printf("NOT ");
				break;
			}
		}
		printf("EVEN\n");
	}
	return 0;
}
