/*
 * p1020 - Rope
 *
 * This seems like a simple geometry problem.
 */
#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793
#define TAU 6.283185307179586

double R;

typedef struct {
	double x;
	double y;
} Nail;


// Describes the equation.
// ax + by + c == 0
typedef struct {
	double a;
	double b;
	double c;
} Line;

Nail nails[100];

void points_to_line(Nail *p1, Nail *p2, Line *l) {
	if (p1->x == p2->x) {
		l->a = 1;
		l->b = 0;
		l->c = -p1->x;
	} else {
		l->b = 1;
		l->a = -(p1->y - p2->y)/(p1->x - p2->x);
		l->c = -(l->a * p1->x) - (l->b * p1->y);
	}
}

double dist(Nail a, Nail b) {
	return hypot(b.x - a.x, b.y - a.y);
}

// we call this for every nail.
double round_bit(Nail *a, Nail *b, Nail *c) {
	Line a1, a2;
	
	// Now we have the lines we need.
	points_to_line(a, b, &a1);
	points_to_line(b, c, &a2);
/*
	printf("L1: %lf %lf %lf\n", a1.a, a1.b, a1.c);
	printf("L2: %lf %lf %lf\n", a2.a, a2.b, a2.c);
	*/

	// Now we need to find the angle between them. We don't care about
	// the sign of the angle, we just need to know the angle.

	double aiai = fabs(atan2(a1.a * a2.b - a2.a * a1.b, a1.a * a2.a + a1.b * a2.b));
/*
	printf("T2: %lf\n", aiai);	
	*/

	return R * (PI - aiai);
}


int main() {
	int N;
	scanf("%d %lf", &N, &R);

	for (int i = 0; i < N; i++) {
		double x, y;
		scanf("%lf %lf", &x, &y);
		nails[i].x = x;
		nails[i].y = y;
	}
	
	// Edge case when N is equal to 1 or 2.
	if (N == 1) {
		double ans = R*TAU;
		printf("%.2lf\n", ans);
		return 0;
	} else if (N == 2) {
		// The distance between the nails, times 2, 2 * PI * R * (PI)/(2 * PI) * 2
		// R * PI * 2 = R * TAU
		double ans = R*TAU + dist(nails[0], nails[1])*2;
		printf("%.2lf\n", ans);
		return 0;
	}
	// These are the two elements we need to consider.
	double round_bits = 0;
	
	// we begin this by calculating from last to first.
	double pure_distance = dist(nails[N-1], nails[0]);

	// Now we calculate between all the others.
	for (int i = 0; i < N-1; i++) {
		pure_distance += dist(nails[i], nails[i+1]);
	}

	// For all of them we also calculate the distance for the three next.
	for (int i = 0; i < N; i++) {
		round_bits += round_bit(nails + i, nails + (i + 1) % N, nails + (i + 2) % N);
	}
	/*
	printf("Pure dist: %lf\n", pure_distance);
	printf("Round bits: %lf\n", round_bits);
	printf("Ans: %.2lf\n", pure_distance + round_bits);
	*/
	printf("%.2lf\n", pure_distance + round_bits);

	return 0;
}
