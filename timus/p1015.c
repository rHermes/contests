/*
 * p1015 - Test the Difference!
 *
 * This was quite a cool task, that I think I solved rather elegantly.
 *
 * There are a max of 30 unique schemes. The way to get to this is
 * that each side can be down and then we can have 4 different rotations
 * for each of these.
 *
 * This gives 6*4 = 24 which is the amount of rotations per scheme.
 *
 * The total amount of permutations is 6! which is 720. If we divide
 * the total number, by the number of rotations per scheme, we get the
 * number of unique schemes. This numbers is then: 720 / 24 = 30.
 *
 * It would be cool to do the normalization with expression templates,
 * but I'll keep it as it is for now. The "which_scheme" function has been
 * checked with a simpler, bruteforce verifier.
 *
 * All functions here have been tested by a simple bruteforce verifier.
 *
 * Another venue that one might be able to persue here is to simply create 
 * a lookup table, for each possible dice, since there are only 720
 * possibilites.
 *
 * I use a simple merge sort to sort the inputs. The inputs are
 * of pairs of (input, first-dice-with-same-scheme). we sort on the 
 * first-dice-with-same-scheme.
 *
 * We could also use a smoothsort here as it might be faster.
 */

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

// This is never used, but it's here just to show all the
// possible states. Their index here is also their index returned from
// ident_scheme
const uint8_t pos_schemes[30][6] = {
	{1, 2, 6, 3, 4, 5 }, {1, 2, 6, 3, 5, 4 }, {1, 2, 6, 4, 3, 5 },
	{1, 2, 6, 4, 5, 3 }, {1, 2, 6, 5, 3, 4 }, {1, 2, 6, 5, 4, 3 },
	{1, 3, 6, 2, 4, 5 }, {1, 3, 6, 2, 5, 4 }, {1, 3, 6, 4, 2, 5 },
	{1, 3, 6, 4, 5, 2 }, {1, 3, 6, 5, 2, 4 }, {1, 3, 6, 5, 4, 2 },
	{1, 4, 6, 2, 3, 5 }, {1, 4, 6, 2, 5, 3 }, {1, 4, 6, 3, 2, 5 },
	{1, 4, 6, 3, 5, 2 }, {1, 4, 6, 5, 2, 3 }, {1, 4, 6, 5, 3, 2 },
	{1, 5, 6, 2, 3, 4 }, {1, 5, 6, 2, 4, 3 }, {1, 5, 6, 3, 2, 4 },
	{1, 5, 6, 3, 4, 2 }, {1, 5, 6, 4, 2, 3 }, {1, 5, 6, 4, 3, 2 },
	{1, 6, 5, 2, 3, 4 }, {1, 6, 5, 2, 4, 3 }, {1, 6, 5, 3, 2, 4 },
	{1, 6, 5, 3, 4, 2 }, {1, 6, 5, 4, 2, 3 }, {1, 6, 5, 4, 3, 2 }
};

// This returns the index of the scheme. we only need to pass in: r, f, d
uint8_t ident_scheme(uint8_t r, uint8_t d, uint8_t f) {
	if (r == 2) {
		if (f == 3) {
			return d == 4 ? 0 : 1;
		} else if (f == 4) {
			return d == 3 ? 2 : 3;
		} else {
			return d == 3 ? 4 : 5;
		}
	} else if (r == 3) {
		if (f == 2) {
			return d == 4 ? 6 : 7;
		} else if (f == 4) {
			return d == 2 ? 8 : 9;
		} else {
			return d == 2 ? 10 : 11;
		}
	} else if (r == 4) {
		if (f == 2) {
			return d == 3 ? 12 : 13;
		} else if (f == 3) {
			return d == 2 ? 14 : 15;
		} else {
			return d == 2 ? 16 : 17;
		}
	} else if (r == 5) {
		if (f == 2) {
			return d == 3 ? 18 : 19;
		} else if (f == 3) {
			return d == 2 ? 20 : 21;
		} else {
			return d == 2 ? 22 : 23;
		}
	} else { 
		if (f == 2) {
			return d == 3 ? 24 : 25;
		} else if (f == 3) {
			return d == 2 ? 26 : 27;
		} else {
			return d == 2 ? 28 : 29;
		}
	}
}

// A normalized dice is one which has 1 on the left side, and then the largest
// number it can on the up side. This function does this, and then uses the
// resulting rotation, to identify the dice, via the ident_scheme function.
//
// This function was first coded and checked up against a brute force method.
// After checking that it normalized all dice correctly, it was then set
// up to return the scheme number. This means that the code now is very hard
// to understand and any rewrite is going to require to start this process
// again.
//
// This is the reason for there being no comment on such ugly code.
// We rotate the cube so that 1 is on the left face and then we make it so
// that the biggest number is on the top of the cube. This way, we normalize
// the direction that it is laying. Then we return a number between 0 and 29
// which is which case of the scheme it is in.
uint8_t normalize(uint8_t l,  uint8_t r, uint8_t u, uint8_t f, uint8_t d, uint8_t b) {
	if (l == 1) {
		uint8_t mm = max(max(u,b), max(d,f));

		if (u == mm) {
			return ident_scheme(r, d, f);
		} else if (b == mm) {
			return ident_scheme(r, f, u);
		} else if (d == mm) {
			return ident_scheme(r, u, b);
		} else {
			return ident_scheme(r, b, d);
		}
	} else if (r == 1) {
		uint8_t mm = max(max(u,b), max(d,f));

		if (u == mm) {
			return ident_scheme(l, d, b);
		} else if (b == mm) {
			return ident_scheme(l, f, d);
		} else if (d == mm) {
			return ident_scheme(l, u, f);
		} else {
			return ident_scheme(l, b, u);
		}
	} else if (u == 1) {
		uint8_t mm = max(max(r,l), max(f,b));

		if (mm == r) {
			return ident_scheme(d, l, f);
		} else if (mm == l) {
			return ident_scheme(d, r, b);
		} else if (mm == f) {
			return ident_scheme(d, b, l);
		} else {
			return ident_scheme(d, f, r);
		}
	} else if (f == 1) {
		uint8_t mm = max(max(l,r), max(u,d));

		if (mm == l) {
			return ident_scheme(b, r, u);
		} else if (mm == r) {
			return ident_scheme(b, l, d);
		} else if (mm == u) {
			return ident_scheme(b, d, r);
		} else {
			return ident_scheme(b, u, l);
		}
	} else if (d == 1) {
		uint8_t mm = max(max(r,l), max(f,b));

		if (mm == r) {
			return ident_scheme(u, l, b);
		} else if (mm == l) {
			return ident_scheme(u, r, f);
		} else if (mm == f) {
			return ident_scheme(u, b, r);
		} else {
			return ident_scheme(u, f, l);
		}
	} else {
		uint8_t mm = max(max(l,r), max(u,d));

		if (mm == l) {
			return ident_scheme(f, r, d);
		} else if (mm == r) {
			return ident_scheme(f, l, u);
		} else if (mm == u) {
			return ident_scheme(f, d, l);
		} else {
			return ident_scheme(f, u, r);
		}
	}
}


typedef struct {
	uint32_t idx;
	uint32_t kind;
} pair;


#define LEESS(a,b) ( (a.kind < b.kind) || (a.kind == b.kind && (a.idx <= b.idx)))

void top_down_merge(pair *A, uint32_t begin, uint32_t middle, uint32_t end, pair *B) {
	uint32_t i, j, k;

	i = begin;
	j = middle;
	for (k = begin; k < end; k++) {
		if (i < middle && (j >= end || LEESS(A[i],A[j]))) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}	
	}
}

void top_down_split_merge(pair *B, uint32_t begin, uint32_t end, pair *A) {
	if (end - begin < 2) {
		return;
	}

	uint32_t middle = (end+begin)/2;
	top_down_split_merge(A, begin, middle, B);
	top_down_split_merge(A, middle, end, B);

	top_down_merge(B, begin, middle, end, A);
}

// Merge sort.
void top_down_mergesort(pair *A, uint32_t n) {
	// We create a copy of the A pair.
	pair *B = malloc(sizeof(pair)*n);
	memcpy(B, A, sizeof(pair)*n);

	top_down_split_merge(B, 0, n, A);

	// now we are done, we can free B.
	free(B);
}

// Get an int.
int getint() {
    int ret = 0, ch;
    while(!isdigit(ch = getc(stdin)));
    ret = ch - '0';
    while(isdigit(ch = getc(stdin)))
        ret = ret*10 + ch - '0';
    return ret;
}
// get a digit.
int getdigit() {
	int ch;
	while(!isdigit(ch = getc(stdin)));
	return ch - '0';
}


int main() {
	// This returns the first of a scheme and the second of a scheme.
	uint32_t first_of_kind[30] = {0};
	uint8_t different = 0;

	uint32_t N = getint();

	// allocate the pairs.
	pair *pairs = malloc(sizeof(pair)*N);
	if (pairs == NULL) {
		return -1;
	}

	for (uint32_t i = 0; i < N; i++) {
		uint8_t l, r, u, f, d, b;
		l = getdigit();
		r = getdigit();
		u = getdigit();
		f = getdigit();
		d = getdigit();
		b = getdigit();

		uint8_t sc = normalize(l, r, u, f, d, b);

		if (first_of_kind[sc] == 0) {
			first_of_kind[sc] = i+1;
			different++;
		}

		pairs[i].idx = i+1;
		pairs[i].kind = (first_of_kind[sc]);
	}

	// Now we sort.
	top_down_mergesort(pairs, N);


	// And now we print.
	printf("%" PRIu8, different);

	uint32_t prev = 0;
	for (uint32_t i = 0; i < N; i++) {
		pair p = pairs[i];
		if (p.kind != prev) {
			prev = p.kind;
			printf("\n%" PRIu32, p.idx);
		} else {
			printf(" %" PRIu32, p.idx);
		}
	}
	printf("\n");
	free(pairs);
	// ok, so since we are going to be outputting the
	return 0;
}
