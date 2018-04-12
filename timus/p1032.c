/*
 * p1032 - Find a Multiple
 *
 * The idea here is that one can prove that there always is an answer and that
 * this answer is a continous sequence of numbers. This means that we want to
 * prove that there is always 1 <= i <= j <= n such that:
 *
 * (a[i] + a[i+1] + ... + a[j-1] + a[j]) % n = 0
 *
 * We can prove this using the pigeonhole principle[1]. We define a function
 *
 * b[i]  = (a[1] + a[2] + ... + a[i-1] + a[i]) % n
 *
 * with b[0] = 0.
 *
 * This function has an output range of [0,n-1], but it as input range of
 * [0, n]. By the pidgeonhole principle, this means that there must atleast
 * two number (i and j) for which b[i] == b[j].
 *
 * We can then define two sums:
 *
 * P1 = a[1] + a[2] + ... + a[i-1] + a[i] = l*n + b[i]
 * P2 = a[1] + a[2] + ... + a[j-1] + a[j] = k*n + b[j]
 * 
 * If we take P2 - P1, we get:
 * 
 * P3 = a[i+1] + a[i+2] + ... + a[j-1] + a[j] = (k-l)*n + b[j] - b[i]
 *
 * since we know that b[j] = b[i], then:
 *
 * P3 = (k-l)*n
 *
 * Which will always be divisible by n.
 * 
 * For this then, we simply find the two points with equal b[x] values and
 * print out the numbers between them. This has O(n) complexity.
 *
 * The idea for this was found at [2].
 *  
 *
 * [1] https://en.wikipedia.org/wiki/Pigeonhole_principle
 * [2] http://acm.timus.ru/forum/thread.aspx?id=8046&upd=634493362398146250
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

int inp[MAX_N];
int acc[MAX_N+1];
int prev[MAX_N+1] = {0};

char buff[16];

int main() {
	fgets(buff, sizeof(buff), stdin);
	int N = strtol(buff, NULL, 10);
	
	int found_start = 0;
	int found_end = 0;
	acc[0] = 0;
	for (int i = 1; i <= N; i++) {
		fgets(buff, sizeof(buff), stdin);
		if (found_end > 0) {
			continue;
		}

		int new_num = strtol(buff, NULL, 10);
		int new_acc = (acc[i-1] + new_num) % N;
		inp[i-1] = new_num;
		acc[i] = new_acc;
		if (new_acc == 0) {
			found_end = i;
		} else if (prev[new_acc] > 0) {
			found_start = prev[new_acc];
			found_end = i;
		} else {
			prev[new_acc] = i;
		}
	}

	printf("%d\n", found_end - found_start);
	for (int i = found_start; i < found_end; i++) {
		printf("%d\n", inp[i]);
	}

	return 0;
}
