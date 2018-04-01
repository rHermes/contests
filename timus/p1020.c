/*
 * p1020 - Rope
 *
 * This seems like a simple geometry problem.
 *
 * This is a VERY simple geometry problem. The answer is always
 * 2*PI*R + sum of distance between the points.
 */
#include <stdio.h>
#include <math.h>

#define TAU 6.283185307179586

typedef struct {
	double x;
	double y;
} Point;

Point nails[100];

double dist(Point a, Point b) {
	return hypot(b.x - a.x, b.y - a.y);
}

int main() {
	double R, ans;
	int N;
	scanf("%d %lf", &N, &R);

	for (int i = 0; i < N; i++) {
		double x, y;
		scanf("%lf %lf", &x, &y);
		nails[i].x = x;
		nails[i].y = y;
	}
	
	// Sum up the distances.
	ans = dist(nails[N-1], nails[0]);
	for (int i = 0; i < N-1; i++) {
		ans += dist(nails[i], nails[i+1]);
	}

	printf("%.2lf\n", TAU*R + ans);

	return 0;
}
