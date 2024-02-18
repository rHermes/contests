#include <string>
#include <cstdio>
#include <vector>
#include <cinttypes>

// Because codeforces has a different view of this.
#define SCU "%" SCNu64 " "
#define SCD "%" SCNd64 " "
#define PRU "%" PRIu64
#define PRD "%" PRId64

using UT = std::uint64_t;
using ST = std::int64_t;


int main() {
	UT T = 0;
	scanf(SCU, &T);

	for (UT t = 0; t < T; t++) {
		UT N = 0;
		scanf(SCU, &N);
		std::vector<int> w(N);
	
		for (UT i = 0; i < N; i++) {
			int c = getc(stdin);
			/* printf("%c\n", c); */
			if (c == '.')
				w[i] = 0;
			else if (c == '@')
				w[i] = 1;
			else
				w[i] = 2;
		}

		UT ans = 0;
		UT i = 0;
		while (i < N && w[i] != 2) {
			if (w[i] == 1)
				ans += 1;

			if (i < N-1) {
				if (w[i+1] == 2)
					i += 2;
				else
					i += 1;
			} else {
				i += 1;
			}
		}

		printf(PRU "\n", ans);

	}
	return 0;
}
