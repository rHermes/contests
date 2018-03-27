/*
 * p1877 - Bicycle Codes
 *
 * Very easy problem. Since he never uses the same lock twice, and we start
 * with the first lock, he will have the first lock out on even tries from
 * the thief and the second lock out on odd tries from the theif. Therefor
 * it is enough to just check and see if the first number is even or the
 * second number is odd.
 */
#include <stdio.h>
#include <inttypes.h>

int main() {
	uint16_t A, B;
	scanf("%" SCNu16 " %" SCNu16, &A, &B);
	printf("%s\n", (A%2 == 0 || B%2 == 1) ? "yes" : "no");
	return 0;
}
