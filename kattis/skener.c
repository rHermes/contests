#include <stdio.h>

int main(void) {
	char buf[50];
	int R, C, ZR, ZC;
	if (scanf("%d %d %d %d", &R, &C, &ZR, &ZC) != 4) {
		perror("invalid input");
		return 1;
	}

	for (int i = 0; i < R; i++) {
		if(scanf("%s", buf) != 1) {
			perror("invalid input");
			return 1;
		}
		
		for (int zi = 0; zi < ZR; zi++) {
			for (int j = 0; j < C; j++) {
				for (int zj = 0; zj < ZC; zj++) {
					printf("%c", buf[j]);
				}
			}
			printf("\n");
		}
	}

	return 0;
}
