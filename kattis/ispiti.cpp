#include <cstdio>
#include <cstdint>
#include <cinttypes>

#include <utility>
#include <vector>
#include <set>
#include <iterator>
#include <map>

#define UINT uint_fast32_t
#define UINT_SCN SCNuFAST32
#define UINT_PRI PRIuFAST32

int main(void) {
	UINT N;
	if(scanf("%" UINT_SCN, &N) != 1) {
		fprintf(stderr, "invalid input\n");
		return 1;
	}

	char c;
	UINT a, b;
	std::map<std::pair<UINT,UINT>,UINT> s;
	std::vector<std::map<std::pair<UINT,UINT>,UINT>::const_iterator> students;
	for (UINT i = 0; i < N; i++) {
		int rc = scanf(" %c %" UINT_SCN "%" UINT_SCN "\n", &c, &a, &b);
		if (rc < 2) {
			printf("%c\n", c);
			fprintf(stderr,"invalid input!\n");
			return 1;
		}

		if (c == 'D') {
			auto [it, _] = s.emplace(std::pair(b, a), s.size()+1);
			students.push_back(it);
		} else if (c == 'P') {
			auto stud = students[a-1];
			/* printf("The %lu student is (%lu, %lu)\n", a, stud->first.first, stud->first.second); */
			auto next = std::next(stud);

			while (next != s.cend()) {
				if (next->first.second >= stud->first.second) {
					printf("%" UINT_PRI "\n", next->second);
					break;
				}
				next = std::next(next);
			}
			if (next == s.cend()) {
				printf("NE\n");
			}

		} else {
			fprintf(stderr,"invalid input!\n");
			return 1;
		}
	}

	/* printf("%" UINT_PRI "\n", dp[n&1][c]); */
	return 0;
}
