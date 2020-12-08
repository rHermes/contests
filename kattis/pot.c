#include <stdio.h>
#include <math.h>
#include <stdint.h>

int main(void) {
	int nums = 0;
	uint64_t ans = 0;
	scanf("%d", &nums);
	for (int i = 0; i < nums; i++) {
		int num;
		scanf("%d", &num);
		int base = num / 10;
		int pot = num % 10;
		
		uint64_t tmp = 1;
		for (int j = 0; j < pot; j++) {
			tmp *= base;
		}
		ans += tmp;
	}
	printf("%lu\n", ans);

	return 0;
}
