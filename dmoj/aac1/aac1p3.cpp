#include <cstdio>
#include <cstdint>
#include <string>

using UT = std::uint64_t;

int main() {
	UT N = 0;
	UT X = 0;
	scanf("%lu %lu", &N, &X);

	std::string out;
	out.reserve(2*N);

	// We can always get the max number of alpacas.
	if (N == X) {
		out.append("1");
		for (UT i = 1; i < N; i++) {
			out.append(" 1");
		}
	} else if ((N - X - 1) % 2 == 0) {
		out = "-1";
	} else {
		out.append("1");
		for (UT i = 0; i < X; i++) {
			out.append(" 1");
		}
		for (UT i = 0; i < (N-X-1); i++) {
			if (i % 2 == 0)
				out.append(" 0");
			else
				out.append(" 1");
		}
	}

	printf("%s\n", out.c_str());

	return 0;
}
