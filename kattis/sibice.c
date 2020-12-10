#include <stdio.h>

int main(void) {
	int N, W, H;
	if(scanf("%d %d %d", &N, &W, &H) != 3) {
		perror("invalid input");
		return 1;
	}
	int l = W*W + H*H;
	for (int i = 0; i < N; i++) {
		int x;
		if (scanf("%d", &x) != 1) {
			perror("invalid input");
			return 1;
		}
		if (x*x <= l) {
			printf("DA\n");
		} else {
			printf("NE\n");
		}
	}
	return 0;
}
