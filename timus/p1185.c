/*
 * p1185 - Wall
 *
 * The idea here is to do a convex hull on the points, then find the answer by
 * calculating the line lengths and adding the amount of wall needed for the
 * corners. This is always going to be 2 * PHI * L, since we are always coming
 * full circle.
 *
 * I use the monotone_chain algorithm, since it does not require a stack. I 
 * use merge sort to sort the points as they come in.
 *
 * [1] https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain#C
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Constants.
#ifndef TAU
#define TAU 6.283185307179586
#endif

#define MAX_N 1000

typedef struct {
	int x;
	int y;
} point;

typedef point* point_ptr;

// Global arrays.
point points[MAX_N];
point_ptr sorted_points_1[MAX_N];
point_ptr sorted_points_2[MAX_N];
point_ptr final_hull[MAX_N+1];

static int ccw(point *p1, point *p2, point *p3) {
	return (p2->x - p1->x)*(p3->y - p1->y) - (p2->y - p1->y)*(p3->x - p1->x);
}


// This takes the sorted point pointers
int convex_hull(point_ptr *points, int npoints) {
	point_ptr *hull;
	int i, t, k = 0;

	hull = final_hull;

	/* lower hull */
	for (i = 0; i < npoints; i++) {
		while ( k >= 2 && ccw(hull[k-2], hull[k-1], points[i]) <= 0) {
			k--;
		}

		hull[k++] = points[i];
	}

	/* upper hull */
	for (i = npoints-2, t = k+1; i >= 0; i--) {
		while ( k >= t && ccw(hull[k-2], hull[k-1], points[i]) <= 0) {
			k--;
		}
		hull[k++] = points[i];
	}

	return k;
}


inline short point_ptr_less(const point* const a, const point *const b) {
	return (a->x == b->x) ? a->y <= b->y : a->x < b->x; 
}

void top_down_merge(point_ptr *A, int begin, int middle, int end, point_ptr *B) {
	int i, j, k;

	i = begin;
	j = middle;
	for (k = begin; k < end; k++) {
		if (i < middle && (j >= end || point_ptr_less(A[i], A[j]))) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}	
	}
}

void top_down_split_merge(point_ptr *B, int begin, int end, point_ptr *A) {
	if (end - begin < 2) {
		return;
	}
	int middle = (end+begin)/2;
	top_down_split_merge(A, begin, middle, B);
	top_down_split_merge(A, middle, end, B);

	top_down_merge(B, begin, middle, end, A);
}

char buff[32];

int main() {
	char *tmp = fgets(buff, sizeof(buff), stdin);
	int N = strtol(tmp, &tmp, 10);
	int L = strtol(tmp, &tmp, 10);

	for (int i = 0; i < N; i++) {
		char *tmp = fgets(buff, sizeof(buff), stdin);
		int x = strtol(tmp, &tmp, 10);
		int y = strtol(tmp, &tmp, 10);

		points[i].x = x;
		points[i].y = y;

		sorted_points_1[i] = &points[i];
		sorted_points_2[i] = &points[i];
	}

	// Sort input points.
	top_down_split_merge(sorted_points_2, 0, N, sorted_points_1);

	// Now we do the convex hull.
	int hullsize = convex_hull(sorted_points_1, N);

	double ans = 0;
	for (int i = 0; i < hullsize-1; i++) {
		point_ptr p1 = final_hull[i];
		point_ptr p2 = final_hull[i+1];
		ans += hypot(p2->x - p1->x, p2->y - p1->y);
	}

	printf("%.0lf\n", ans + L*TAU);


	return 0;
}
