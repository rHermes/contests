/*
 * p1028 - Stars
 *
 * This might done with some kind of partial sum?
 *
 * f(x,y) = s(x,y) + s(x,y-1) + s(x,y - 1) ..
 *
 * Where S(y) is the amount of stars. We could also create a graph from this
 * and do longest possible way? This would not work however. What one would
 * have to do is to record the number of total stars you can accumulate to
 * a certain node and this is expensive.
 *
 * The time limit is low however, so maybe this isn't the way?
 *
 * Another way to do this is to have sort of data structure where I can query
 * for number of points less than a certain X address. After star is considered,
 * I add it to this datastructure, and then continue. This would always be correct,
 * since the stars are listed in such an acending ordered.
 */

#include <cstdio>
#include <iterator>
#include <utility>
#include <set>

int res[15000] = {0};

int main() {
	// This is results.
	// Create a map over the stars.
	std::set<std::pair<int,int>> stars;

	int N, x, y;
	scanf("%d\n", &N);

	// Having 1 element in this map, makes this much easier and faster.
	scanf("%d %d\n", &x, &y);
	stars.emplace(x, y);
	res[0]++;

	for (int i = 1; i < N; i++) {
		scanf("%d %d\n", &x, &y);

		// Now we try to find the x coordinate.
		auto it = stars.upper_bound(std::make_pair(x, y));

		// The distance from this to the beginning is the amount of stars we are
		// over.
		int dist;
		if (it == stars.end()) {
			dist = stars.size();
		} else {
			dist = std::distance(stars.begin(),it);
		}

		res[dist]++;

		stars.emplace(x, y);
		// This is the previous version 
	}
	// Print out the result.
	for (int i = 0; i < N; i++) {
		printf("%d\n", res[i]);
	}
	return 0;
}

