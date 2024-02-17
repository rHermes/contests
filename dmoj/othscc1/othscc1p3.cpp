#include <cstdio>
#include <cstdint>
#include <vector>
#include <unordered_set>
#include <map>
#include <cmath>

using UT = std::uint64_t;
using ST = std::int64_t;

int main() {
	UT N = 0;
	ST D = 0;
	scanf("%lu %ld\n", &N, &D);


	// large value to handle the first one.
	ST prev = -1000000000000000;
	std::vector<std::vector<UT>> G(N);
	for (UT i = 0; i < N; i++) {
		ST h;
		scanf("%lu\n", &h);

		if (std::abs(h - prev) <= D) {
			G[i].push_back(i-1);
			G[i-1].push_back(i);
		}

		prev = h;
	}


	// Now we need to see how many graphs there are and which is the biggest.
	std::vector<bool> seen(N);
	UT maxSize = 0;
	UT count = 0;
	for (UT i = 0; i < N; i++) {
		if (seen[i])
			continue;

		count++;

		// Now we need to find the size.
		std::vector<UT> Q = {i};
		UT ourSize = 0;
		while (!Q.empty()) {
			const auto cur = Q.back();
			Q.pop_back();

			if (seen[cur])
				continue;
			seen[cur] = true;

			ourSize++;
			for (const auto& next : G[cur]) {
				if (seen[next])
					continue;

				Q.push_back(next);
			}
		}

		maxSize = std::max(maxSize, ourSize);
	}

	
	printf("%lu\n%lu\n", count, maxSize);

	return 0;
}
