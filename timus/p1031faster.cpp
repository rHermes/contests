/*
 * p1031 - Railway Tickets
 *
 * This is based on [1] and it uses queues to get the work done.
 *
 * [1] https://github.com/Otrebus/timus/blob/master/1031.cpp
 */

#include <algorithm>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>


int main() {
	int C[3], L[3], N, s, t;

	std::queue<std::pair<int, int>> q[3]; // <distance, cost> for each type of ticket
	scanf("%d %d %d %d %d %d %d %d %d", L, L+1, L+2, C, C+1, C+2, &N, &s, &t);

	if (s > t) {
		std::swap(s, t);
	}

	std::vector<int> v; // Station distances.
	v.reserve(N+1);
	v.emplace_back(0);
	v.emplace_back(0);

	while(--N) {
		int x;
		scanf("%d", &x);
		v.emplace_back(x);
	}

	// Initialize the ticket ranges from the first station.
	for (int i = 0; i < 3; i++) {
		q[i].emplace(L[i] + v[s], C[i]);
	}

	int c = std::numeric_limits<int>::max();
	for (int i = s + 1; i <= t; i++) {
		int l = v[i];

		// First we remove the tickets until we get them in range.
		for (int j = 0; j < 3; j++) {
			while (!q[j].empty() && q[j].front().first < l) {
				q[j].pop();
			}
		}
		c = std::numeric_limits<int>::max();
		if (!q[0].empty()) {
			c = std::min(c, q[0].front().second);
		}
		if (!q[1].empty()) {
			c = std::min(c, q[1].front().second);
		}
		if (!q[2].empty()) {
			c = std::min(c, q[2].front().second);
		}

		// Now we go forward.
		for (int j = 0; j < 3; j++) {
			q[j].emplace(L[j]+l, c+C[j]);
		}
	}
	
	printf("%d\n", c);

	return 0;
}
