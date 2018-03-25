/*
 * p1003 - Parity
 *
 * There are many ways to solve this problem.
 *
 * The one from the original competition reads in all the answers and while doing so,
 * sorts the answers by their starting point. No two ranges are allowed to store
 * the start point. If two ranges do have the same start point, it will either have
 * the same endpoint or it will not. If it has, then it's either a contrediciton
 * or useless. If not, then we must just perform a split, to get 2 new parts.
 *
 *
 * The one I am going to be implementing is a DSU solution. This explenation is
 * the combination of the one from the codeforces link and the java code.
 *
 * We have a function f(n) which tells us if the sequence has been even up to
 * this point. if it has then f(n) = 0 and if it hasn't then it gives f(n) = 1
 *
 * f(0) = 0 then, because this is an empty sequence.
 *
 * So, if we get the information that the sequence has an even number of 
 * ones from L to R, then this must mean that f(R) == f(L-1), since 
 * if f(L-1) is odd, then adding an even number of ones to it, is going to
 * give you an odd number, and if f(L-1) is even then adding an even
 * number of ones to it will give you an even number.
 *
 * This is opposite if we get to know that the sequence from L to R is odd,
 * in which case it will change the parity, meaning that f(R) != f(L-1).
 *
 * With this in mind, we can use a DSU to solve this. K means that f(K) is
 * even and -K means that f(K) is odd. This is a way of encoding information.
 * Each time we get a interval in, we do:
 *
 * if (even):
 *	dsu.union(L-1, R)
 *	dsu.union(-(L-1), -R)
 * else:
 *  dsu.union(L-1, -R)
 *  dsu.union(-(L-1), R)
 *
 * We add for both the possibility that f(L-1) is even and that f(L-1) is
 * negative in each case.
 *
 * We can then simply check if (L-1) and -(L-1) or R and -R is in the 
 * same set and if they are, we have a contradiction.
 *
 * As you can see this implementation is in C++. This could have been done
 * in C, if you have an array of id -> "integer". You have corresponding arrays
 * for each of the other nodes. This requires you to scan through that array
 * for the ID each time though, so I decided to go with C++, for it's map feature.
 *
 * LINKS:
 *
 * http://codeforces.com/blog/entry/2835?#comment-57563
 * https://github.com/DarkWishMaster/ACM-TIMUS-RU/blob/master/1003.%20Parity.java
 * https://github.com/Otrebus/timus/blob/master/1003.cpp
 * https://github.com/marioyc/Online-Judge-Solutions/blob/master/Timus%20Online%20Judge/1003%20-%20Parity.cpp
 * https://www.fi.muni.cz/ceoi1999/parity/PARITY.PAS
 */

#include <unordered_map>
#include <cstdio>
#include <cinttypes>

class DSU {
	private:
		std::unordered_map<int32_t,int32_t> parent;
		std::unordered_map<int32_t,int32_t> rank;

	public:
		void make_set(int32_t x) {
			parent.emplace(x, x);
			rank.emplace(x,0);
		}
		
		// We use path compression here.
		int32_t find(int32_t x) {
			int32_t y = parent[x];
			if (y != x) {
				int32_t z = find(y);
				parent[y] = z;
				return z;
			}
			return x;
		}

		// union is apparently a c++ keyword.	
		void unite(int32_t x, int32_t y) {
			x = find(x);
			y = find(y);

			if (x == y) {
				return;
			}

			int32_t x_rank = rank[x];
			int32_t y_rank = rank[y];

			if (x_rank < y_rank) {
				parent[x] = y;
			} else if (x_rank > y_rank) {
				parent[y] = x;
			} else {
				parent[x] = y;
				rank[y]++;
			}
		}


		void clear() {
			parent.clear();
			rank.clear();
		}
};

int main() {
	DSU dsu;
	while (true) {
		dsu.clear();
		int32_t N, M;
		scanf("%" SCNd32 "\n%" SCNd32, &N, &M);
		if (N < 0) {
			break;
		}

		char buff[6];
		int32_t res = M;
		for (int32_t i = 0; i < M; i++) {
			int32_t a, b;
			scanf("%" SCNd32 " %" SCNd32 " %s\n", &a, &b, buff);
			// We use R+1, instead of L-1, because this elimitates the possibility
			// of L-1 becoming 0, which would result in a and -a being the same.
			b++;

			if (res != M) {
				continue;
			}

			if (a > N || b > N + 1) {
				res = i;
				continue;
			}

			// We create the variables.
			dsu.make_set(a);
			dsu.make_set(-a);
			dsu.make_set(b);
			dsu.make_set(-b);

			if (buff[0] == 'e') {
				// even
				dsu.unite(a, b);
				dsu.unite(-a,-b);
			} else {
				// odd
				dsu.unite(a, -b);
				dsu.unite(-a, b);
			}

			// Now we simply need to check if this works.
			if (dsu.find(a) == dsu.find(-a) || dsu.find(b) == dsu.find(-b)) {
				res = i;
			}
		}
		printf("%" PRId32 "\n", res);
	}
	return 0;
}
