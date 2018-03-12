/*
 * p. 1005 Stone pile
 *
 *
 * This is a two-way partition problem. I use the CKK to find the
 * best solution.
 *
 * http://web.cecs.pdx.edu/~bart/cs510ai/papers/korf-ckk.pdf
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


int32_t KK2(int32_t a, int32_t b) {
	return a - b;
}

int32_t KK3(int32_t a, int32_t b, int32_t c) {
	int32_t d = a-b;
	if (d > c) {
		return KK2(d,c);
	} else {
		return KK2(c,d);
	}
}

int32_t KK4(int32_t a, int32_t b, int32_t c, int32_t d) {
	int32_t t1 = a-b;

	if (t1 < d) {
		return KK3(c, d, t1);
	} else if (t1 < c) {
		return KK3(c, t1, d);
	} else {
		return KK3(t1, c, d);
	}
}
// We assume a couple of things here.
// 1, we assume that p is sorted in descending order.
int32_t CKK(int32_t *p, int sz) {
	// insert check for if P is less than 4 here.
	
	// We only check if it is KK4, because we can do this check, on the outside.
	if (sz == 4) {
		return KK4(p[0], p[1], p[2], p[3]);
	}
	
	// Now we check if the sum is larger than the body.
	int32_t q = p[0];

	for (int i = 1; i < sz; i++) {
		q -= p[i];
	}

	if (q >= 0) {
		return q;
	}


	int32_t a = p[0];
	int32_t b = p[1];

	int32_t *pr = malloc((sz-1)*sizeof(*pr));

	// for the right branch, we know that it will be in the front of the list.
	memcpy(pr+1, p+2, (sz-2)*sizeof(*p));
	pr[0] = a + b;

	// we then 
	int32_t ans1 = CKK(pr, sz-1);
	free(pr);

	if (ans1 == 0) {
		return 0;
	}

	// The left is a little worse. We end up doing this from the 
	int32_t *pl = malloc((sz-1)*sizeof(*pl));

	memcpy(pl, p+2, (sz-2)*sizeof(*p));
	pl[sz-2] = a-b;

	// Now we simply loop through, and once we find the first one
	// we are smaller than, we have the right place.
	for (int k = sz-3; k >= 0; k--) {
		if (pl[k] > a-b) {
			break;
		} else {
			pl[k+1] = pl[k];
			pl[k] = a-b;
		}
	}

	int32_t ans2 = CKK(pl, sz-1);
	free(pl);

	if (ans1 < ans2) {
		return ans1;
	} else {
		return ans2;
	}
}

// This allows us to make the check once and then think about it
// no more.
int32_t CKK_call(int32_t *p, int sz) {
	if (sz == 1) {
        return p[0];
    } else if (sz == 2) {
        return KK2(p[0], p[1]);
    } else if (sz == 3) {
        return KK3(p[0], p[1], p[2]);
    } else if (sz == 4) {
		return KK4(p[0], p[1], p[2], p[3]);
	} else {
		return CKK(p, sz);
	}
}


int main() {
	int num;
	int32_t in[20];

	scanf("%d",&num);

	for (int kk = 0; kk < num; kk++) {
		int t = 0;
		scanf("%d", &t);
		
		int i = 0;
		// Now we do a simple insert sort.
		for (i = 0; i < kk; i++) {
			if (in[i] < t) {
				break;
			}
		}

		// For now we push all the other ones one forward.
		for (int j = kk; j > i; j--) {
			in[j] = in[j-1];
		}

		in[i] = t;
	}

	int32_t ans = CKK_call(in, num);

	printf("%d\n", ans);
	return 0;
}
