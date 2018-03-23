/*
 * p1015 - Test the Difference!
 *
 * This was quite a cool task, that I think I solved rather elegantly.
 *
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
 */

#include <stdio.h>
#include <stdbool.h>
#include <cinttypes>

#include <algorithm>
#include <array>
#include <iostream>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define FILL_SCHEME(a, l, r, u, d, f, b) \
	a[0] = l; a[1] = r; \
	a[2] = u; a[4] = d; \
	a[3] = f; a[5] = b;

typedef uint8_t scheme[6];

// places.
#define L 0
#define R 1
#define U 2
#define F 3
#define D 4
#define B 5


// So a normalization is quite simple.
// We rotate the cube so that 1 is on the left face and then we make it so
// that the biggest number is on the top of the cube.
void normalize(scheme a, scheme out) {
	// the various sides.
	uint8_t l = a[L];
	uint8_t r = a[R];
	uint8_t u = a[U];
	uint8_t f = a[F];
	uint8_t d = a[D];
	uint8_t b = a[B];

	if (l == 1) {
		// 1 is on the left side.
		// This can be optimized, but it would create a lot of code.
		uint8_t mm = max(max(u,b), max(d,f));

		if (u == mm) {
			// up is largest.
			FILL_SCHEME(out, l, r, u, d, f, b)
		} else if (b == mm) {
			// back is the largest.
			FILL_SCHEME(out, l, r, b, f, u, d)
		} else if (d == mm) {
			// down is the largest.
			FILL_SCHEME(out, l, r, d, u, b, f)
		} else {
			// front is the largest.
			FILL_SCHEME(out, l, r, f, b, d, u)
		}
	} else if (r == 1) {
		// 1 is on the right side.
		uint8_t mm = max(max(u,b), max(d,f));

		if (u == mm) {
			// up is largest.
			FILL_SCHEME(out, r, l, u, d, b, f)
		} else if (b == mm) {
			// back is the largest.
			FILL_SCHEME(out, r, l, f, b, u, d)
		} else if (d == mm) {
			// down is the largest.
			FILL_SCHEME(out, r, l, d, u, f, b)
		} else {
			// front is the largest.
			FILL_SCHEME(out, r, l, b, f, d, u)
		}
	} else if (u == 1) {
		// 1 is on the top side.

	} else if (f == 1) {
		// 1 is on the front side.

	} else if (d == 1) {
		// 1 is on the bottom side.

	} else {
		// 1 is on the back side.

	}
}

void sort_scheme(scheme a, scheme out) {
	// For now just copy it out.
	// There are 3 pairs always. F,B L,R, U,D
	uint8_t f, b, l, r, u, d;

	l = min(a[0], a[1]);
	r = max(a[0], a[1]);

	u = min(a[2], a[4]);
	d = max(a[2], a[4]);

	f = min(a[3], a[5]);
	b = max(a[3], a[5]);

	// We assign these pairs, and once we do, we
	// sort them after wards on their first element.
	
	// We can optimize this later.
	bool lu = l < u;
	bool lf = l < f;
	bool uf = u < f;
	
	if (lu) {
		if (uf) {
			// l u f
			FILL_SCHEME(out, l, r, u, d, f, b)
		} else if (lf) {
			// l f u
			FILL_SCHEME(out, l, r, f, b, u, d)
		} else {
			// f l u
			FILL_SCHEME(out, f, b, l, r, u, d)
		}
	} else {
		if (lf) {
			// u l f
			FILL_SCHEME(out, u, d, l, r, f, b)
		} else if (uf) {
			// u f l
			FILL_SCHEME(out, u, d, f, b, l, r)
		} else {
			// f u l
			FILL_SCHEME(out, f, b, u, d, l, r)
		}
	}
}

int main() {
	std::array<uint8_t,6> perms = {1, 2, 3, 4, 5, 6};

	scheme a;
	scheme b;
	do {
		// Copy over the values.
		a[0] = perms[0];
		a[1] = perms[1];
		a[2] = perms[2];
		a[3] = perms[3];
		a[4] = perms[4];
		a[5] = perms[5];

		sort_scheme(a, b);

		for (int i = 0; i < 6; i++) {
			printf("%" PRIu8 " ", b[i]);
		}
		/*
		for (const auto&s : perms) {
			printf("%" PRIu8 " ", s);
		}
		*/
		printf("\n");
	} while (std::next_permutation(perms.begin(), perms.end()));
	return 0;
}
