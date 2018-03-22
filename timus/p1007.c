/*
 * p1007 - Code Words
 *
 * This could be done faster. The trick is to recognize here that removing a digit
 * reduces the sum by the ones to the left of it.
 *
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Returns the position of the first swap or 0 if nothing.
int first_case(bool *a, int N) {
	// Any one of them could be replaced.
	// first calculate the sum.
	int sum = 0;
	for (int i = 0; i < N; i++) {
		if (a[i]) {
			sum += N-i;
		}
	}

	// Now we must just see how close we are to being correct.
	return (sum % (N+1));
}

// inserting a 0 at a given spot is the same as adding
// the number of ones to the left of that to the sum.
//
// adding a 1 is the same, except we also add the number
// we are at.
int second_case(bool *a, int N) {
	int sum = 0;
	int marks = 0;
	for (int i = 0; i < N-1; i++) {
		if (a[N-2-i]) {
			sum += i+1;
			marks++;
		}
	}

	// Ok now it is simple, we just have to loop through the
	// array and see if we get it. 
	for (int i = 0; i < N; i++) {
		// Sum if we insert a 0 is just the marks left + total 
		int sum1 = sum + marks; // marks_left[i];

		if (a[N-2-i]) {
			marks--;
		}

		if (sum1 % (N+1) == 0) {
			// Inserting 0 
			return -(i+1);
		} else if ((sum1 + (i+1)) % (N+1) == 0) {
			// inserting 1
			return i+1;
		}
	}

	return 0;
}

int third_case(bool *a, int N) {
	// first we get the sum.
	int sum = 0;
	int marks = 0;
	for (int i = 0; i < N+1; i++) {
		if (a[N-i]) {
			sum += i+1;
			marks++;
		}
	}

	for (int i = 0; i < N+1; i++) {
		int sum1 = sum - marks;
		if (a[N-i]) {
			marks--;
			sum1 -= i;
		}

		if (sum1 % (N+1) == 0) {
			return i;
		}
	}
	
	// we we remove a 0, we just remove marks left.
	return -1;
}


// So here is the gist of it:
// output from first_case is 0 which is that the input is fine or i+1
// output from second_case is i+1 if a 1 should be inserted and -(i+1) if a 0 should be inserted.
// output from the third_case is i which is the number for which we don't print.

int main() {
	int N;
	scanf("%d\n", &N);

	bool arr[1001];

	bool run = true;

	for (int i = 0; run ; i++) {
		int K = 0;
		while (1) {
			int rc = getchar();
			if (rc == EOF) {
				run = false;
				break;
			}
			if (rc == '\n' || rc == '\0') {
				break;
			}
			if (rc == ' ') {
				continue;
			}

			arr[K] = rc == '1';

			K++;
		}
		if (K < 3) {
			continue;
		}

		if (K == N) {
			int rc = first_case(arr, N);
			if (rc != 0) {
				arr[N-rc] = 0;
			}
			for (int i = 0; i < N; i++) {
				printf("%d", arr[i]);
			}
			printf("\n");
		} else if (K == (N-1)) {
			int rc = second_case(arr, N);
			int add;
			bool what_to_add;

			// decide what thing to add.
			if (rc < 0) {
				add = N+rc;
				what_to_add = false;
			} else {
				add = N-rc;
				what_to_add = true;
			}
			
			int k = 0;
			for (int i = 0; i < N; i++) {
				if (add == 0) {
					add = -1;
					printf("%d", what_to_add);
				}  else {
					printf("%d", arr[k]);
					k++;
					add--;
				}
			}

			printf("\n");
			
		} else if (K == (N+1)) {
			int rc = third_case(arr, N);
			for (int i = 0; i < N+1; i++) {
				if (i != N-rc) {
					printf("%d", arr[i]);
				}
			}
			printf("\n");
		} else {
			printf("WTF?!?!\n");
		}
	}
	
	return 0;
}
