#include <cstdio>
#include <cinttypes>

#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <cmath>

using UT = std::uint64_t;
using ST = std::int64_t;

int main() {
	UT T = 0;
	scanf("%lu", &T);

	for (UT i = 0; i < T; i++) {
		UT K = 0;
		UT X = 0;
		UT A = 0;
		scanf("%lu %lu %lu", &K, &X, &A);
		
		/* printf("We have %lu %lu %lu\n", K, X, A); */

		if (A <= X) {
			printf("NO\n");
			continue;
		}

		/* if ((A-X)*K <= A) { */
		/* 	printf("NO\n"); */
		/* 	continue; */
		/* } */
	

		bool good = true;
		const UT OGA = A;

		// We assume one loss.
		UT coins_left = A-1;
		for (UT j = 1; j < X; j++) {

			// we have to get
			// coins_left - BI + BI*K > OGA
			// (BI-1)*K > OGA - coins_left
			// BI-1 > (OGA - coins_left) / K
			//

			UT minBI = (OGA - coins_left) / (K-1);
			minBI += 1;
			/* printf("Bet %lu is %lu\n", j, minBI); */

			if (coins_left <= minBI) {
				good = false;
				break;
			}
			coins_left -= minBI;
		}

		// And now, we must have that coins_left * K > OGA
		if (good) {
			good = OGA < (coins_left * K);
		}

		
		if (good)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
