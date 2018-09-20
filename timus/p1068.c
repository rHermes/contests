/*
 * p1068 - Sum
 */
#include <stdio.h>
#include <inttypes.h>

int main() {
	int64_t tmp;
	scanf("%" SCNd64, &tmp);

	if (tmp > 0) {
		printf("%" PRId64 "\n", (tmp*(tmp+1))/2);
	} else {
		printf("%" PRId64 "\n", -((tmp*(tmp-1))/2 - 1));
	}
	return 0;
}
