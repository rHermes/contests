/**
 * tle17c3p6 - TLE '17 Contest 3 P6 - Donut Coupons
 *
 * Jesus Christ, this is the most finicky task I've ever completed, this one took a lot of
 * tries, 20 to be exact, and 5 days, even when I had read the editorial! It's also one
 * of the cooler tasks I've done and it combined multiple different areas. This one will
 * be really important to document, as it's not very intuitive!
 *
 * My first attempt was actually to use a segment tree in python. I had a feeling that
 * for large update ranges, this was going to be way to slow and I was right. At least
 * I had something which produced the right results.
 *
 * The first thing to notice here is of course that since we are going to be doing
 * everything in MOD 10**9 + 7, we can use modular exponentiation for the series. I'll
 * be using M = 10**9 + 7 from now on. It's also worth noting that M is prime, meaning
 * that we have a finite field. This is important, as we need this to ensure that
 * we can use multiplicative inverse later.
 *
 * After having tried some different things, I ended up reading the editorial for this
 * one.
 *
 *
 * Frustrated with not getting the right answers, I went with another idea, maybe
 * using lazy segment trees could work. The idea here is that we don't update the
 * values immidiatly. Instead, we add another 2 values to each node:
 *
 * - is_lazy = does this node have pending lazy updates?
 * - lazy_value = a 4 tuple pair of (l, r, k, original_l)
 *
 * The lazy value is used to calculate the amount to add to the current node. Initially
 * I only included (l, r, k) which was a mistake, but we come back to that later. We 
 * add one more operation to the tree too, which is `push_down(v, tl, tr)`. This
 * operation checks if the node v is lazy, and if it is, it adds the lazy value
 * to the current node, then if the node has children, it calls `push_down` on them
 * too, before making them lazy and adding the lazy values to the appropriate nodes.
 * In essence it makes the node v not lazy, if it is lazy.
 *
 * With this setup, updating the tree becomes calling `push_down` on the root node
 * and then setting it's lazy_value and making it lazy.
 *
 * The query function remains the same, but in the beginning of the function we
 * call `push_down` on the node we are in, to make sure it's not lazy.
 *
 * With this setup, we get bulk updates and queries ideally only update the parts
 * of the tree that we are interested in.
 *
 * We have the same issue as before here, where we need to know the sum of
 * S(l, r, k). The way I solved this here was to pre-calculate the sums
 * for all N and K, and just use those tables when looking up.
 *
 * This didn't come out correctly either, and I finally bit the bullet and
 * designed a simple python program which generates test inputs and compares
 * the output of programs with the slow correct way. This uncovered multiple
 * bugs in my code quite quickly.
 *
 * The biggest problem was that I had forgotten 
 *
 */
#include <cstdio>
#include <cstdint>

#include <stdexcept>

#include <array>
#include <vector>
#include <deque>

using UT = std::uint64_t;
using ST = std::int64_t;

constexpr ST MAX_K = 11;
/* constexpr UT MAX_K = 3; */
constexpr ST MOD_M = 1000000007;

// The multiplicative inverse of MAX_K! ^- 1 mod MOD_M
constexpr ST INVERSE_MAX_K = 571199524;

inline ST pmod(ST i, ST n) {
    return (i % n + n) % n;
}

ST ipow(ST base, UT exp, ST m) {
	ST res = 1;
	base = pmod(base, m);

	if (base == 0)
		return 0;


	while (exp > 0) {
		if (exp % 2 == 1)
			res = pmod(res * base, m);

		exp >>= 1;
		base = pmod(base*base, m);
	}

	return res;
}


class BinaryIndexedTree {
	private:
		std::vector<ST> tree_;

		[[nodiscard]] inline ST getParent(ST index) const {
			return (index & (index + 1)) - 1;
		}

		[[nodiscard]] inline ST getNext(ST index) const {
			return index | (index + 1);
		}

	public:

		BinaryIndexedTree() {}

		explicit BinaryIndexedTree(UT n) {
			tree_.resize(n);
		}

		void add(ST index, ST delta) {
			while (static_cast<UT>(index) < tree_.size()) {
				tree_[static_cast<UT>(index)] = pmod(tree_[static_cast<UT>(index)] + delta, MOD_M);
				index = getNext(index);
			}
		}

		[[nodiscard]] ST prefixSum(ST index) const {
			ST ret = 0;

			while (0 <= index) {
				ret = pmod(ret + tree_[static_cast<UT>(index)], MOD_M);
				index = getParent(index);
			}

			return ret;
		}
};

class PowerTree {
	private:
		std::array<BinaryIndexedTree, MAX_K+1> bits_;
		UT n_{0};

	public:

		explicit PowerTree(UT n) : n_{n} {
			std::fill(bits_.begin(), bits_.end(), BinaryIndexedTree(n+1));
		}
		
		ST query(ST l) {
			ST ret = 0;
			for (UT i = 0; i < bits_.size(); i++) {
				ret = pmod(ret + ipow(l, i, MOD_M)*bits_[i].prefixSum(l), MOD_M);
			}
			return pmod(ret * INVERSE_MAX_K, MOD_M);
		}

		ST query(ST l, ST r) {
			if (l == 1) {
				return pmod(query(r), MOD_M);
			} else {
				return pmod(query(r) - query(l-1), MOD_M);
			}
		}

		void update(ST l, ST r, UT k) {
			// This was generated with the tle17c3p6-eq-generator.py script.
			switch (k) {
				case 0:
					bits_[0].add(r + 1, 39916800*r);
					bits_[0].add(l, 39916800 - 39916800*l);
					bits_[1].add(l, 39916800);
					bits_[1].add(r + 1, 960083207);
					break;
				case 1:
					bits_[0].add(r + 1, pmod(960083207 * l, MOD_M)*r + 19958400*ipow(r, 2, MOD_M) + 59875200*r);
					bits_[0].add(l, 19958400*ipow(l, 2, MOD_M) - 59875200*l + 39916800);
					bits_[1].add(l, 59875200 - 39916800*l);
					bits_[1].add(r + 1, 39916800*l - 59875200);
					bits_[2].add(l, 19958400);
					bits_[2].add(r + 1, 980041607);
					break;
				case 2:
					bits_[0].add(r + 1, pmod(39916800 * ipow(l, 2, MOD_M), MOD_M)*r - pmod(39916800 * l, MOD_M)*ipow(r, 2, MOD_M) - pmod(119750400 * l, MOD_M)*r + 13305600*ipow(r, 3, MOD_M) + 59875200*ipow(r, 2, MOD_M) + 86486400*r);
					bits_[0].add(l, 986694407*ipow(l, 3, MOD_M) + 59875200*ipow(l, 2, MOD_M) - 86486400*l + 39916800);
					bits_[1].add(l, 39916800*ipow(l, 2, MOD_M) - 119750400*l + 86486400);
					bits_[1].add(r + 1, 960083207*ipow(l, 2, MOD_M) + 119750400*l - 86486400);
					bits_[2].add(l, 59875200 - 39916800*l);
					bits_[2].add(r + 1, 39916800*l - 59875200);
					bits_[3].add(l, 13305600);
					bits_[3].add(r + 1, 986694407);
					break;
				case 3:
					bits_[0].add(r + 1, pmod(960083207 * ipow(l, 3, MOD_M), MOD_M)*r + pmod(59875200 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(179625600 * ipow(l, 2, MOD_M), MOD_M)*r - pmod(39916800 * l, MOD_M)*ipow(r, 3, MOD_M) - pmod(179625600 * l, MOD_M)*ipow(r, 2, MOD_M) - pmod(259459200 * l, MOD_M)*r + 9979200*ipow(r, 4, MOD_M) + 59875200*ipow(r, 3, MOD_M) + 129729600*ipow(r, 2, MOD_M) + 119750400*r);
					bits_[0].add(l, 9979200*ipow(l, 4, MOD_M) - 59875200*ipow(l, 3, MOD_M) + 129729600*ipow(l, 2, MOD_M) - 119750400*l + 39916800);
					bits_[1].add(l, 960083207*ipow(l, 3, MOD_M) + 179625600*ipow(l, 2, MOD_M) - 259459200*l + 119750400);
					bits_[1].add(r + 1, 39916800*ipow(l, 3, MOD_M) - 179625600*ipow(l, 2, MOD_M) + 259459200*l - 119750400);
					bits_[2].add(l, 59875200*ipow(l, 2, MOD_M) - 179625600*l + 129729600);
					bits_[2].add(r + 1, 940124807*ipow(l, 2, MOD_M) + 179625600*l - 129729600);
					bits_[3].add(l, 59875200 - 39916800*l);
					bits_[3].add(r + 1, 39916800*l - 59875200);
					bits_[4].add(l, 9979200);
					bits_[4].add(r + 1, 990020807);
					break;
				case 4:
					bits_[0].add(r + 1, pmod(39916800 * ipow(l, 4, MOD_M), MOD_M)*r - pmod(79833600 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 2, MOD_M) - pmod(239500800 * ipow(l, 3, MOD_M), MOD_M)*r + pmod(79833600 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 3, MOD_M) + pmod(359251200 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(518918400 * ipow(l, 2, MOD_M), MOD_M)*r - pmod(39916800 * l, MOD_M)*ipow(r, 4, MOD_M) - pmod(239500800 * l, MOD_M)*ipow(r, 3, MOD_M) - pmod(518918400 * l, MOD_M)*ipow(r, 2, MOD_M) - pmod(479001600 * l, MOD_M)*r + 7983360*ipow(r, 5, MOD_M) + 59875200*ipow(r, 4, MOD_M) + 172972800*ipow(r, 3, MOD_M) + 239500800*ipow(r, 2, MOD_M) + 158336640*r);
					bits_[0].add(l, 992016647*ipow(l, 5, MOD_M) + 59875200*ipow(l, 4, MOD_M) - 172972800*ipow(l, 3, MOD_M) + 239500800*ipow(l, 2, MOD_M) - 158336640*l + 39916800);
					bits_[1].add(l, 39916800*ipow(l, 4, MOD_M) - 239500800*ipow(l, 3, MOD_M) + 518918400*ipow(l, 2, MOD_M) - 479001600*l + 158336640);
					bits_[1].add(r + 1, 960083207*ipow(l, 4, MOD_M) + 239500800*ipow(l, 3, MOD_M) - 518918400*ipow(l, 2, MOD_M) + 479001600*l - 158336640);
					bits_[2].add(l, 920166407*ipow(l, 3, MOD_M) + 359251200*ipow(l, 2, MOD_M) - 518918400*l + 239500800);
					bits_[2].add(r + 1, 79833600*ipow(l, 3, MOD_M) - 359251200*ipow(l, 2, MOD_M) + 518918400*l - 239500800);
					bits_[3].add(l, 79833600*ipow(l, 2, MOD_M) - 239500800*l + 172972800);
					bits_[3].add(r + 1, 920166407*ipow(l, 2, MOD_M) + 239500800*l - 172972800);
					bits_[4].add(l, 59875200 - 39916800*l);
					bits_[4].add(r + 1, 39916800*l - 59875200);
					bits_[5].add(l, 7983360);
					bits_[5].add(r + 1, 992016647);
					break;
				case 5:
					bits_[0].add(r + 1, pmod(960083207 * ipow(l, 5, MOD_M), MOD_M)*r + pmod(99792000 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(299376000 * ipow(l, 4, MOD_M), MOD_M)*r - pmod(133056000 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 3, MOD_M) - pmod(598752000 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 2, MOD_M) - pmod(864864000 * ipow(l, 3, MOD_M), MOD_M)*r + pmod(99792000 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 4, MOD_M) + pmod(598752000 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 3, MOD_M) + pmod(297295993 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(197503993 * ipow(l, 2, MOD_M), MOD_M)*r - pmod(39916800 * l, MOD_M)*ipow(r, 5, MOD_M) - pmod(299376000 * l, MOD_M)*ipow(r, 4, MOD_M) - pmod(864864000 * l, MOD_M)*ipow(r, 3, MOD_M) - pmod(197503993 * l, MOD_M)*ipow(r, 2, MOD_M) - pmod(791683200 * l, MOD_M)*r + 6652800*ipow(r, 6, MOD_M) + 59875200*ipow(r, 5, MOD_M) + 216216000*ipow(r, 4, MOD_M) + 399168000*ipow(r, 3, MOD_M) + 395841600*ipow(r, 2, MOD_M) + 199584000*r);
					bits_[0].add(l, 6652800*ipow(l, 6, MOD_M) - 59875200*ipow(l, 5, MOD_M) + 216216000*ipow(l, 4, MOD_M) - 399168000*ipow(l, 3, MOD_M) + 395841600*ipow(l, 2, MOD_M) - 199584000*l + 39916800);
					bits_[1].add(l, 960083207*ipow(l, 5, MOD_M) + 299376000*ipow(l, 4, MOD_M) - 864864000*ipow(l, 3, MOD_M) + 197503993*ipow(l, 2, MOD_M) - 791683200*l + 199584000);
					bits_[1].add(r + 1, 39916800*ipow(l, 5, MOD_M) - 299376000*ipow(l, 4, MOD_M) + 864864000*ipow(l, 3, MOD_M) - 197503993*ipow(l, 2, MOD_M) + 791683200*l - 199584000);
					bits_[2].add(l, 99792000*ipow(l, 4, MOD_M) - 598752000*ipow(l, 3, MOD_M) + 297295993*ipow(l, 2, MOD_M) - 197503993*l + 395841600);
					bits_[2].add(r + 1, 900208007*ipow(l, 4, MOD_M) + 598752000*ipow(l, 3, MOD_M) - 297295993*ipow(l, 2, MOD_M) + 197503993*l - 395841600);
					bits_[3].add(l, 866944007*ipow(l, 3, MOD_M) + 598752000*ipow(l, 2, MOD_M) - 864864000*l + 399168000);
					bits_[3].add(r + 1, 133056000*ipow(l, 3, MOD_M) - 598752000*ipow(l, 2, MOD_M) + 864864000*l - 399168000);
					bits_[4].add(l, 99792000*ipow(l, 2, MOD_M) - 299376000*l + 216216000);
					bits_[4].add(r + 1, 900208007*ipow(l, 2, MOD_M) + 299376000*l - 216216000);
					bits_[5].add(l, 59875200 - 39916800*l);
					bits_[5].add(r + 1, 39916800*l - 59875200);
					bits_[6].add(l, 6652800);
					bits_[6].add(r + 1, 993347207);
					break;
				case 6:
					bits_[0].add(r + 1, pmod(39916800 * ipow(l, 6, MOD_M), MOD_M)*r - pmod(119750400 * ipow(l, 5, MOD_M), MOD_M)*ipow(r, 2, MOD_M) - pmod(359251200 * ipow(l, 5, MOD_M), MOD_M)*r + pmod(199584000 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 3, MOD_M) + pmod(898128000 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(297295993 * ipow(l, 4, MOD_M), MOD_M)*r - pmod(199584000 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 4, MOD_M) - pmod(197503993 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 3, MOD_M) - pmod(594591986 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 2, MOD_M) - pmod(395007986 * ipow(l, 3, MOD_M), MOD_M)*r + pmod(119750400 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 5, MOD_M) + pmod(898128000 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 4, MOD_M) + pmod(594591986 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 3, MOD_M) + pmod(592511979 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(375049586 * ipow(l, 2, MOD_M), MOD_M)*r - pmod(39916800 * l, MOD_M)*ipow(r, 6, MOD_M) - pmod(359251200 * l, MOD_M)*ipow(r, 5, MOD_M) - pmod(297295993 * l, MOD_M)*ipow(r, 4, MOD_M) - pmod(395007986 * l, MOD_M)*ipow(r, 3, MOD_M) - pmod(375049586 * l, MOD_M)*ipow(r, 2, MOD_M) - pmod(197503993 * l, MOD_M)*r + 5702400*ipow(r, 7, MOD_M) + 59875200*ipow(r, 6, MOD_M) + 259459200*ipow(r, 5, MOD_M) + 598752000*ipow(r, 4, MOD_M) + 791683200*ipow(r, 3, MOD_M) + 598752000*ipow(r, 2, MOD_M) + 240451200*r);
					bits_[0].add(l, 994297607*ipow(l, 7, MOD_M) + 59875200*ipow(l, 6, MOD_M) - 259459200*ipow(l, 5, MOD_M) + 598752000*ipow(l, 4, MOD_M) - 791683200*ipow(l, 3, MOD_M) + 598752000*ipow(l, 2, MOD_M) - 240451200*l + 39916800);
					bits_[1].add(l, 39916800*ipow(l, 6, MOD_M) - 359251200*ipow(l, 5, MOD_M) + 297295993*ipow(l, 4, MOD_M) - 395007986*ipow(l, 3, MOD_M) + 375049586*ipow(l, 2, MOD_M) - 197503993*l + 240451200);
					bits_[1].add(r + 1, 960083207*ipow(l, 6, MOD_M) + 359251200*ipow(l, 5, MOD_M) - 297295993*ipow(l, 4, MOD_M) + 395007986*ipow(l, 3, MOD_M) - 375049586*ipow(l, 2, MOD_M) + 197503993*l - 240451200);
					bits_[2].add(l, 880249607*ipow(l, 5, MOD_M) + 898128000*ipow(l, 4, MOD_M) - 594591986*ipow(l, 3, MOD_M) + 592511979*ipow(l, 2, MOD_M) - 375049586*l + 598752000);
					bits_[2].add(r + 1, 119750400*ipow(l, 5, MOD_M) - 898128000*ipow(l, 4, MOD_M) + 594591986*ipow(l, 3, MOD_M) - 592511979*ipow(l, 2, MOD_M) + 375049586*l - 598752000);
					bits_[3].add(l, 199584000*ipow(l, 4, MOD_M) - 197503993*ipow(l, 3, MOD_M) + 594591986*ipow(l, 2, MOD_M) - 395007986*l + 791683200);
					bits_[3].add(r + 1, 800416007*ipow(l, 4, MOD_M) + 197503993*ipow(l, 3, MOD_M) - 594591986*ipow(l, 2, MOD_M) + 395007986*l - 791683200);
					bits_[4].add(l, 800416007*ipow(l, 3, MOD_M) + 898128000*ipow(l, 2, MOD_M) - 297295993*l + 598752000);
					bits_[4].add(r + 1, 199584000*ipow(l, 3, MOD_M) - 898128000*ipow(l, 2, MOD_M) + 297295993*l - 598752000);
					bits_[5].add(l, 119750400*ipow(l, 2, MOD_M) - 359251200*l + 259459200);
					bits_[5].add(r + 1, 880249607*ipow(l, 2, MOD_M) + 359251200*l - 259459200);
					bits_[6].add(l, 59875200 - 39916800*l);
					bits_[6].add(r + 1, 39916800*l - 59875200);
					bits_[7].add(l, 5702400);
					bits_[7].add(r + 1, 994297607);
					break;
				case 7:
					bits_[0].add(r + 1, pmod(960083207 * ipow(l, 7, MOD_M), MOD_M)*r + pmod(139708800 * ipow(l, 6, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(419126400 * ipow(l, 6, MOD_M), MOD_M)*r - pmod(279417600 * ipow(l, 5, MOD_M), MOD_M)*ipow(r, 3, MOD_M) - pmod(257379193 * ipow(l, 5, MOD_M), MOD_M)*ipow(r, 2, MOD_M) - pmod(816214393 * ipow(l, 5, MOD_M), MOD_M)*r + pmod(349272000 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 4, MOD_M) + pmod(95631986 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 3, MOD_M) + pmod(540535972 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(191263972 * ipow(l, 4, MOD_M), MOD_M)*r - pmod(279417600 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 5, MOD_M) - pmod(95631986 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 4, MOD_M) - pmod(54047958 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 3, MOD_M) - pmod(382527944 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 2, MOD_M) - pmod(541782365 * ipow(l, 3, MOD_M), MOD_M)*r + pmod(139708800 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 6, MOD_M) + pmod(257379193 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 5, MOD_M) + pmod(540535972 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 4, MOD_M) + pmod(382527944 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 3, MOD_M) + pmod(312673544 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(191263972 * ipow(l, 2, MOD_M), MOD_M)*r - pmod(39916800 * l, MOD_M)*ipow(r, 7, MOD_M) - pmod(419126400 * l, MOD_M)*ipow(r, 6, MOD_M) - pmod(816214393 * l, MOD_M)*ipow(r, 5, MOD_M) - pmod(191263972 * l, MOD_M)*ipow(r, 4, MOD_M) - pmod(541782365 * l, MOD_M)*ipow(r, 3, MOD_M) - pmod(191263972 * l, MOD_M)*ipow(r, 2, MOD_M) - pmod(683158393 * l, MOD_M)*r + 4989600*ipow(r, 8, MOD_M) + 59875200*ipow(r, 7, MOD_M) + 302702400*ipow(r, 6, MOD_M) + 838252800*ipow(r, 5, MOD_M) + 385445593*ipow(r, 4, MOD_M) + 397087993*ipow(r, 3, MOD_M) + 841579200*ipow(r, 2, MOD_M) + 279417600*r);
					bits_[0].add(l, 4989600*ipow(l, 8, MOD_M) - 59875200*ipow(l, 7, MOD_M) + 302702400*ipow(l, 6, MOD_M) - 838252800*ipow(l, 5, MOD_M) + 385445593*ipow(l, 4, MOD_M) - 397087993*ipow(l, 3, MOD_M) + 841579200*ipow(l, 2, MOD_M) - 279417600*l + 39916800);
					bits_[1].add(l, 960083207*ipow(l, 7, MOD_M) + 419126400*ipow(l, 6, MOD_M) - 816214393*ipow(l, 5, MOD_M) + 191263972*ipow(l, 4, MOD_M) - 541782365*ipow(l, 3, MOD_M) + 191263972*ipow(l, 2, MOD_M) - 683158393*l + 279417600);
					bits_[1].add(r + 1, 39916800*ipow(l, 7, MOD_M) - 419126400*ipow(l, 6, MOD_M) + 816214393*ipow(l, 5, MOD_M) - 191263972*ipow(l, 4, MOD_M) + 541782365*ipow(l, 3, MOD_M) - 191263972*ipow(l, 2, MOD_M) + 683158393*l - 279417600);
					bits_[2].add(l, 139708800*ipow(l, 6, MOD_M) - 257379193*ipow(l, 5, MOD_M) + 540535972*ipow(l, 4, MOD_M) - 382527944*ipow(l, 3, MOD_M) + 312673544*ipow(l, 2, MOD_M) - 191263972*l + 841579200);
					bits_[2].add(r + 1, 860291207*ipow(l, 6, MOD_M) + 257379193*ipow(l, 5, MOD_M) - 540535972*ipow(l, 4, MOD_M) + 382527944*ipow(l, 3, MOD_M) - 312673544*ipow(l, 2, MOD_M) + 191263972*l - 841579200);
					bits_[3].add(l, 720582407*ipow(l, 5, MOD_M) + 95631986*ipow(l, 4, MOD_M) - 54047958*ipow(l, 3, MOD_M) + 382527944*ipow(l, 2, MOD_M) - 541782365*l + 397087993);
					bits_[3].add(r + 1, 279417600*ipow(l, 5, MOD_M) - 95631986*ipow(l, 4, MOD_M) + 54047958*ipow(l, 3, MOD_M) - 382527944*ipow(l, 2, MOD_M) + 541782365*l - 397087993);
					bits_[4].add(l, 349272000*ipow(l, 4, MOD_M) - 95631986*ipow(l, 3, MOD_M) + 540535972*ipow(l, 2, MOD_M) - 191263972*l + 385445593);
					bits_[4].add(r + 1, 650728007*ipow(l, 4, MOD_M) + 95631986*ipow(l, 3, MOD_M) - 540535972*ipow(l, 2, MOD_M) + 191263972*l - 385445593);
					bits_[5].add(l, 720582407*ipow(l, 3, MOD_M) + 257379193*ipow(l, 2, MOD_M) - 816214393*l + 838252800);
					bits_[5].add(r + 1, 279417600*ipow(l, 3, MOD_M) - 257379193*ipow(l, 2, MOD_M) + 816214393*l - 838252800);
					bits_[6].add(l, 139708800*ipow(l, 2, MOD_M) - 419126400*l + 302702400);
					bits_[6].add(r + 1, 860291207*ipow(l, 2, MOD_M) + 419126400*l - 302702400);
					bits_[7].add(l, 59875200 - 39916800*l);
					bits_[7].add(r + 1, 39916800*l - 59875200);
					bits_[8].add(l, 4989600);
					bits_[8].add(r + 1, 995010407);
					break;
				case 8:
					bits_[0].add(r + 1, pmod(39916800 * ipow(l, 8, MOD_M), MOD_M)*r - pmod(159667200 * ipow(l, 7, MOD_M), MOD_M)*ipow(r, 2, MOD_M) - pmod(479001600 * ipow(l, 7, MOD_M), MOD_M)*r + pmod(372556800 * ipow(l, 6, MOD_M), MOD_M)*ipow(r, 3, MOD_M) + pmod(676505593 * ipow(l, 6, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(421619186 * ipow(l, 6, MOD_M), MOD_M)*r - pmod(558835200 * ipow(l, 5, MOD_M), MOD_M)*ipow(r, 4, MOD_M) - pmod(353011179 * ipow(l, 5, MOD_M), MOD_M)*ipow(r, 3, MOD_M) - pmod(264857551 * ipow(l, 5, MOD_M), MOD_M)*ipow(r, 2, MOD_M) - pmod(706022358 * ipow(l, 5, MOD_M), MOD_M)*r + pmod(558835200 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 5, MOD_M) + pmod(191263972 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 4, MOD_M) + pmod(108095916 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 3, MOD_M) + pmod(765055888 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(83564723 * ipow(l, 4, MOD_M), MOD_M)*r - pmod(372556800 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 6, MOD_M) - pmod(353011179 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 5, MOD_M) - pmod(108095916 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 4, MOD_M) - pmod(353407846 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 3, MOD_M) - pmod(167129446 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 2, MOD_M) - pmod(176703923 * ipow(l, 3, MOD_M), MOD_M)*r + pmod(159667200 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 7, MOD_M) + pmod(676505593 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 6, MOD_M) + pmod(264857551 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 5, MOD_M) + pmod(765055888 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 4, MOD_M) + pmod(167129446 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 3, MOD_M) + pmod(765055888 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(732633558 * ipow(l, 2, MOD_M), MOD_M)*r - pmod(39916800 * l, MOD_M)*ipow(r, 8, MOD_M) - pmod(479001600 * l, MOD_M)*ipow(r, 7, MOD_M) - pmod(421619186 * l, MOD_M)*ipow(r, 6, MOD_M) - pmod(706022358 * l, MOD_M)*ipow(r, 5, MOD_M) - pmod(83564723 * l, MOD_M)*ipow(r, 4, MOD_M) - pmod(176703923 * l, MOD_M)*ipow(r, 3, MOD_M) - pmod(732633558 * l, MOD_M)*ipow(r, 2, MOD_M) - pmod(235340786 * l, MOD_M)*r + 4435200*ipow(r, 9, MOD_M) + 59875200*ipow(r, 8, MOD_M) + 345945600*ipow(r, 7, MOD_M) + 117670393*ipow(r, 6, MOD_M) + 216712946*ipow(r, 5, MOD_M) + 794175986*ipow(r, 4, MOD_M) + 244211186*ipow(r, 3, MOD_M) + 117670393*ipow(r, 2, MOD_M) + 318003840*r);
					bits_[0].add(l, 995564807*ipow(l, 9, MOD_M) + 59875200*ipow(l, 8, MOD_M) - 345945600*ipow(l, 7, MOD_M) + 117670393*ipow(l, 6, MOD_M) - 216712946*ipow(l, 5, MOD_M) + 794175986*ipow(l, 4, MOD_M) - 244211186*ipow(l, 3, MOD_M) + 117670393*ipow(l, 2, MOD_M) - 318003840*l + 39916800);
					bits_[1].add(l, 39916800*ipow(l, 8, MOD_M) - 479001600*ipow(l, 7, MOD_M) + 421619186*ipow(l, 6, MOD_M) - 706022358*ipow(l, 5, MOD_M) + 83564723*ipow(l, 4, MOD_M) - 176703923*ipow(l, 3, MOD_M) + 732633558*ipow(l, 2, MOD_M) - 235340786*l + 318003840);
					bits_[1].add(r + 1, 960083207*ipow(l, 8, MOD_M) + 479001600*ipow(l, 7, MOD_M) - 421619186*ipow(l, 6, MOD_M) + 706022358*ipow(l, 5, MOD_M) - 83564723*ipow(l, 4, MOD_M) + 176703923*ipow(l, 3, MOD_M) - 732633558*ipow(l, 2, MOD_M) + 235340786*l - 318003840);
					bits_[2].add(l, 840332807*ipow(l, 7, MOD_M) + 676505593*ipow(l, 6, MOD_M) - 264857551*ipow(l, 5, MOD_M) + 765055888*ipow(l, 4, MOD_M) - 167129446*ipow(l, 3, MOD_M) + 765055888*ipow(l, 2, MOD_M) - 732633558*l + 117670393);
					bits_[2].add(r + 1, 159667200*ipow(l, 7, MOD_M) - 676505593*ipow(l, 6, MOD_M) + 264857551*ipow(l, 5, MOD_M) - 765055888*ipow(l, 4, MOD_M) + 167129446*ipow(l, 3, MOD_M) - 765055888*ipow(l, 2, MOD_M) + 732633558*l - 117670393);
					bits_[3].add(l, 372556800*ipow(l, 6, MOD_M) - 353011179*ipow(l, 5, MOD_M) + 108095916*ipow(l, 4, MOD_M) - 353407846*ipow(l, 3, MOD_M) + 167129446*ipow(l, 2, MOD_M) - 176703923*l + 244211186);
					bits_[3].add(r + 1, 627443207*ipow(l, 6, MOD_M) + 353011179*ipow(l, 5, MOD_M) - 108095916*ipow(l, 4, MOD_M) + 353407846*ipow(l, 3, MOD_M) - 167129446*ipow(l, 2, MOD_M) + 176703923*l - 244211186);
					bits_[4].add(l, 441164807*ipow(l, 5, MOD_M) + 191263972*ipow(l, 4, MOD_M) - 108095916*ipow(l, 3, MOD_M) + 765055888*ipow(l, 2, MOD_M) - 83564723*l + 794175986);
					bits_[4].add(r + 1, 558835200*ipow(l, 5, MOD_M) - 191263972*ipow(l, 4, MOD_M) + 108095916*ipow(l, 3, MOD_M) - 765055888*ipow(l, 2, MOD_M) + 83564723*l - 794175986);
					bits_[5].add(l, 558835200*ipow(l, 4, MOD_M) - 353011179*ipow(l, 3, MOD_M) + 264857551*ipow(l, 2, MOD_M) - 706022358*l + 216712946);
					bits_[5].add(r + 1, 441164807*ipow(l, 4, MOD_M) + 353011179*ipow(l, 3, MOD_M) - 264857551*ipow(l, 2, MOD_M) + 706022358*l - 216712946);
					bits_[6].add(l, 627443207*ipow(l, 3, MOD_M) + 676505593*ipow(l, 2, MOD_M) - 421619186*l + 117670393);
					bits_[6].add(r + 1, 372556800*ipow(l, 3, MOD_M) - 676505593*ipow(l, 2, MOD_M) + 421619186*l - 117670393);
					bits_[7].add(l, 159667200*ipow(l, 2, MOD_M) - 479001600*l + 345945600);
					bits_[7].add(r + 1, 840332807*ipow(l, 2, MOD_M) + 479001600*l - 345945600);
					bits_[8].add(l, 59875200 - 39916800*l);
					bits_[8].add(r + 1, 39916800*l - 59875200);
					bits_[9].add(l, 4435200);
					bits_[9].add(r + 1, 995564807);
					break;
				case 9:
					bits_[0].add(r + 1, pmod(960083207 * ipow(l, 9, MOD_M), MOD_M)*r + pmod(179625600 * ipow(l, 8, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(538876800 * ipow(l, 8, MOD_M), MOD_M)*r - pmod(479001600 * ipow(l, 7, MOD_M), MOD_M)*ipow(r, 3, MOD_M) - pmod(155507186 * ipow(l, 7, MOD_M), MOD_M)*ipow(r, 2, MOD_M) - pmod(113510379 * ipow(l, 7, MOD_M), MOD_M)*r + pmod(838252800 * ipow(l, 6, MOD_M), MOD_M)*ipow(r, 4, MOD_M) + pmod(29516765 * ipow(l, 6, MOD_M), MOD_M)*ipow(r, 3, MOD_M) + pmod(897286330 * ipow(l, 6, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(59033530 * ipow(l, 6, MOD_M), MOD_M)*r - pmod(5903353 * ipow(l, 5, MOD_M), MOD_M)*ipow(r, 5, MOD_M) - pmod(544275151 * ipow(l, 5, MOD_M), MOD_M)*ipow(r, 4, MOD_M) - pmod(794572653 * ipow(l, 5, MOD_M), MOD_M)*ipow(r, 3, MOD_M) - pmod(177100590 * ipow(l, 5, MOD_M), MOD_M)*ipow(r, 2, MOD_M) - pmod(950416507 * ipow(l, 5, MOD_M), MOD_M)*r + pmod(838252800 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 6, MOD_M) + pmod(544275151 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 5, MOD_M) + pmod(243215811 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 4, MOD_M) + pmod(295167650 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 3, MOD_M) + pmod(876041257 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(147583825 * ipow(l, 4, MOD_M), MOD_M)*r - pmod(479001600 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 7, MOD_M) - pmod(29516765 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 6, MOD_M) - pmod(794572653 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 5, MOD_M) - pmod(295167650 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 4, MOD_M) - pmod(501388338 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 3, MOD_M) - pmod(295167650 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 2, MOD_M) - pmod(197900660 * ipow(l, 3, MOD_M), MOD_M)*r + pmod(179625600 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 8, MOD_M) + pmod(155507186 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 7, MOD_M) + pmod(897286330 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 6, MOD_M) + pmod(177100590 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 5, MOD_M) + pmod(876041257 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 4, MOD_M) + pmod(295167650 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 3, MOD_M) + pmod(296850990 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(59033530 * ipow(l, 2, MOD_M), MOD_M)*r - pmod(39916800 * l, MOD_M)*ipow(r, 9, MOD_M) - pmod(538876800 * l, MOD_M)*ipow(r, 8, MOD_M) - pmod(113510379 * l, MOD_M)*ipow(r, 7, MOD_M) - pmod(59033530 * l, MOD_M)*ipow(r, 6, MOD_M) - pmod(950416507 * l, MOD_M)*ipow(r, 5, MOD_M) - pmod(147583825 * l, MOD_M)*ipow(r, 4, MOD_M) - pmod(197900660 * l, MOD_M)*ipow(r, 3, MOD_M) - pmod(59033530 * l, MOD_M)*ipow(r, 2, MOD_M) - pmod(862034546 * l, MOD_M)*r + 3991680*ipow(r, 10, MOD_M) + 59875200*ipow(r, 9, MOD_M) + 389188800*ipow(r, 8, MOD_M) + 437004793*ipow(r, 7, MOD_M) + 325069419*ipow(r, 6, MOD_M) + 29516765*ipow(r, 5, MOD_M) + 49475165*ipow(r, 4, MOD_M) + 353011179*ipow(r, 3, MOD_M) + 431017273*ipow(r, 2, MOD_M) + 359251200*r);
					bits_[0].add(l, 3991680*ipow(l, 10, MOD_M) - 59875200*ipow(l, 9, MOD_M) + 389188800*ipow(l, 8, MOD_M) - 437004793*ipow(l, 7, MOD_M) + 325069419*ipow(l, 6, MOD_M) - 29516765*ipow(l, 5, MOD_M) + 49475165*ipow(l, 4, MOD_M) - 353011179*ipow(l, 3, MOD_M) + 431017273*ipow(l, 2, MOD_M) - 359251200*l + 39916800);
					bits_[1].add(l, 960083207*ipow(l, 9, MOD_M) + 538876800*ipow(l, 8, MOD_M) - 113510379*ipow(l, 7, MOD_M) + 59033530*ipow(l, 6, MOD_M) - 950416507*ipow(l, 5, MOD_M) + 147583825*ipow(l, 4, MOD_M) - 197900660*ipow(l, 3, MOD_M) + 59033530*ipow(l, 2, MOD_M) - 862034546*l + 359251200);
					bits_[1].add(r + 1, 39916800*ipow(l, 9, MOD_M) - 538876800*ipow(l, 8, MOD_M) + 113510379*ipow(l, 7, MOD_M) - 59033530*ipow(l, 6, MOD_M) + 950416507*ipow(l, 5, MOD_M) - 147583825*ipow(l, 4, MOD_M) + 197900660*ipow(l, 3, MOD_M) - 59033530*ipow(l, 2, MOD_M) + 862034546*l - 359251200);
					bits_[2].add(l, 179625600*ipow(l, 8, MOD_M) - 155507186*ipow(l, 7, MOD_M) + 897286330*ipow(l, 6, MOD_M) - 177100590*ipow(l, 5, MOD_M) + 876041257*ipow(l, 4, MOD_M) - 295167650*ipow(l, 3, MOD_M) + 296850990*ipow(l, 2, MOD_M) - 59033530*l + 431017273);
					bits_[2].add(r + 1, 820374407*ipow(l, 8, MOD_M) + 155507186*ipow(l, 7, MOD_M) - 897286330*ipow(l, 6, MOD_M) + 177100590*ipow(l, 5, MOD_M) - 876041257*ipow(l, 4, MOD_M) + 295167650*ipow(l, 3, MOD_M) - 296850990*ipow(l, 2, MOD_M) + 59033530*l - 431017273);
					bits_[3].add(l, 520998407*ipow(l, 7, MOD_M) + 29516765*ipow(l, 6, MOD_M) - 794572653*ipow(l, 5, MOD_M) + 295167650*ipow(l, 4, MOD_M) - 501388338*ipow(l, 3, MOD_M) + 295167650*ipow(l, 2, MOD_M) - 197900660*l + 353011179);
					bits_[3].add(r + 1, 479001600*ipow(l, 7, MOD_M) - 29516765*ipow(l, 6, MOD_M) + 794572653*ipow(l, 5, MOD_M) - 295167650*ipow(l, 4, MOD_M) + 501388338*ipow(l, 3, MOD_M) - 295167650*ipow(l, 2, MOD_M) + 197900660*l - 353011179);
					bits_[4].add(l, 838252800*ipow(l, 6, MOD_M) - 544275151*ipow(l, 5, MOD_M) + 243215811*ipow(l, 4, MOD_M) - 295167650*ipow(l, 3, MOD_M) + 876041257*ipow(l, 2, MOD_M) - 147583825*l + 49475165);
					bits_[4].add(r + 1, 161747207*ipow(l, 6, MOD_M) + 544275151*ipow(l, 5, MOD_M) - 243215811*ipow(l, 4, MOD_M) + 295167650*ipow(l, 3, MOD_M) - 876041257*ipow(l, 2, MOD_M) + 147583825*l - 49475165);
					bits_[5].add(l, 994096654*ipow(l, 5, MOD_M) + 544275151*ipow(l, 4, MOD_M) - 794572653*ipow(l, 3, MOD_M) + 177100590*ipow(l, 2, MOD_M) - 950416507*l + 29516765);
					bits_[5].add(r + 1, 5903353*ipow(l, 5, MOD_M) - 544275151*ipow(l, 4, MOD_M) + 794572653*ipow(l, 3, MOD_M) - 177100590*ipow(l, 2, MOD_M) + 950416507*l - 29516765);
					bits_[6].add(l, 838252800*ipow(l, 4, MOD_M) - 29516765*ipow(l, 3, MOD_M) + 897286330*ipow(l, 2, MOD_M) - 59033530*l + 325069419);
					bits_[6].add(r + 1, 161747207*ipow(l, 4, MOD_M) + 29516765*ipow(l, 3, MOD_M) - 897286330*ipow(l, 2, MOD_M) + 59033530*l - 325069419);
					bits_[7].add(l, 520998407*ipow(l, 3, MOD_M) + 155507186*ipow(l, 2, MOD_M) - 113510379*l + 437004793);
					bits_[7].add(r + 1, 479001600*ipow(l, 3, MOD_M) - 155507186*ipow(l, 2, MOD_M) + 113510379*l - 437004793);
					bits_[8].add(l, 179625600*ipow(l, 2, MOD_M) - 538876800*l + 389188800);
					bits_[8].add(r + 1, 820374407*ipow(l, 2, MOD_M) + 538876800*l - 389188800);
					bits_[9].add(l, 59875200 - 39916800*l);
					bits_[9].add(r + 1, 39916800*l - 59875200);
					bits_[10].add(l, 3991680);
					bits_[10].add(r + 1, 996008327);
					break;
				case 10:
					bits_[0].add(r + 1, pmod(39916800 * ipow(l, 10, MOD_M), MOD_M)*r - pmod(199584000 * ipow(l, 9, MOD_M), MOD_M)*ipow(r, 2, MOD_M) - pmod(598752000 * ipow(l, 9, MOD_M), MOD_M)*r + pmod(598752000 * ipow(l, 8, MOD_M), MOD_M)*ipow(r, 3, MOD_M) + pmod(694383986 * ipow(l, 8, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(891887979 * ipow(l, 8, MOD_M), MOD_M)*r - pmod(197503993 * ipow(l, 7, MOD_M), MOD_M)*ipow(r, 4, MOD_M) - pmod(185023951 * ipow(l, 7, MOD_M), MOD_M)*ipow(r, 3, MOD_M) - pmod(567551895 * ipow(l, 7, MOD_M), MOD_M)*ipow(r, 2, MOD_M) - pmod(370047902 * ipow(l, 7, MOD_M), MOD_M)*r + pmod(676505593 * ipow(l, 6, MOD_M), MOD_M)*ipow(r, 5, MOD_M) + pmod(573791916 * ipow(l, 6, MOD_M), MOD_M)*ipow(r, 4, MOD_M) + pmod(324287748 * ipow(l, 6, MOD_M), MOD_M)*ipow(r, 3, MOD_M) + pmod(295167650 * ipow(l, 6, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(250694169 * ipow(l, 6, MOD_M), MOD_M)*r - pmod(676505593 * ipow(l, 5, MOD_M), MOD_M)*ipow(r, 6, MOD_M) - pmod(88550295 * ipow(l, 5, MOD_M), MOD_M)*ipow(r, 5, MOD_M) - pmod(486431622 * ipow(l, 5, MOD_M), MOD_M)*ipow(r, 4, MOD_M) - pmod(590335300 * ipow(l, 5, MOD_M), MOD_M)*ipow(r, 3, MOD_M) - pmod(752082507 * ipow(l, 5, MOD_M), MOD_M)*ipow(r, 2, MOD_M) - pmod(295167650 * ipow(l, 5, MOD_M), MOD_M)*r + pmod(197503993 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 7, MOD_M) + pmod(573791916 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 6, MOD_M) + pmod(486431622 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 5, MOD_M) + pmod(737919125 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 4, MOD_M) + pmod(253470838 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 3, MOD_M) + pmod(737919125 * ipow(l, 4, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(494751650 * ipow(l, 4, MOD_M), MOD_M)*r - pmod(598752000 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 8, MOD_M) - pmod(185023951 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 7, MOD_M) - pmod(324287748 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 6, MOD_M) - pmod(590335300 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 5, MOD_M) - pmod(253470838 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 4, MOD_M) - pmod(650558831 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 3, MOD_M) - pmod(989503300 * ipow(l, 3, MOD_M), MOD_M)*ipow(r, 2, MOD_M) - pmod(530111769 * ipow(l, 3, MOD_M), MOD_M)*r + pmod(199584000 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 9, MOD_M) + pmod(694383986 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 8, MOD_M) + pmod(567551895 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 7, MOD_M) + pmod(295167650 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 6, MOD_M) + pmod(752082507 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 5, MOD_M) + pmod(737919125 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 4, MOD_M) + pmod(989503300 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 3, MOD_M) + pmod(295167650 * ipow(l, 2, MOD_M), MOD_M)*ipow(r, 2, MOD_M) + pmod(310172702 * ipow(l, 2, MOD_M), MOD_M)*r - pmod(39916800 * l, MOD_M)*ipow(r, 10, MOD_M) - pmod(598752000 * l, MOD_M)*ipow(r, 9, MOD_M) - pmod(891887979 * l, MOD_M)*ipow(r, 8, MOD_M) - pmod(370047902 * l, MOD_M)*ipow(r, 7, MOD_M) - pmod(250694169 * l, MOD_M)*ipow(r, 6, MOD_M) - pmod(295167650 * l, MOD_M)*ipow(r, 5, MOD_M) - pmod(494751650 * l, MOD_M)*ipow(r, 4, MOD_M) - pmod(530111769 * l, MOD_M)*ipow(r, 3, MOD_M) - pmod(310172702 * l, MOD_M)*ipow(r, 2, MOD_M) - pmod(592511979 * l, MOD_M)*r + 3628800*ipow(r, 11, MOD_M) + 59875200*ipow(r, 10, MOD_M) + 432432000*ipow(r, 9, MOD_M) + 796255993*ipow(r, 8, MOD_M) + 750099172*ipow(r, 7, MOD_M) + 382527944*ipow(r, 6, MOD_M) + 98950330*ipow(r, 5, MOD_M) + 382527944*ipow(r, 4, MOD_M) + 770057572*ipow(r, 3, MOD_M) + 796255993*ipow(r, 2, MOD_M) + 402192000*r);
					bits_[0].add(l, 996371207*ipow(l, 11, MOD_M) + 59875200*ipow(l, 10, MOD_M) - 432432000*ipow(l, 9, MOD_M) + 796255993*ipow(l, 8, MOD_M) - 750099172*ipow(l, 7, MOD_M) + 382527944*ipow(l, 6, MOD_M) - 98950330*ipow(l, 5, MOD_M) + 382527944*ipow(l, 4, MOD_M) - 770057572*ipow(l, 3, MOD_M) + 796255993*ipow(l, 2, MOD_M) - 402192000*l + 39916800);
					bits_[1].add(l, 39916800*ipow(l, 10, MOD_M) - 598752000*ipow(l, 9, MOD_M) + 891887979*ipow(l, 8, MOD_M) - 370047902*ipow(l, 7, MOD_M) + 250694169*ipow(l, 6, MOD_M) - 295167650*ipow(l, 5, MOD_M) + 494751650*ipow(l, 4, MOD_M) - 530111769*ipow(l, 3, MOD_M) + 310172702*ipow(l, 2, MOD_M) - 592511979*l + 402192000);
					bits_[1].add(r + 1, 960083207*ipow(l, 10, MOD_M) + 598752000*ipow(l, 9, MOD_M) - 891887979*ipow(l, 8, MOD_M) + 370047902*ipow(l, 7, MOD_M) - 250694169*ipow(l, 6, MOD_M) + 295167650*ipow(l, 5, MOD_M) - 494751650*ipow(l, 4, MOD_M) + 530111769*ipow(l, 3, MOD_M) - 310172702*ipow(l, 2, MOD_M) + 592511979*l - 402192000);
					bits_[2].add(l, 800416007*ipow(l, 9, MOD_M) + 694383986*ipow(l, 8, MOD_M) - 567551895*ipow(l, 7, MOD_M) + 295167650*ipow(l, 6, MOD_M) - 752082507*ipow(l, 5, MOD_M) + 737919125*ipow(l, 4, MOD_M) - 989503300*ipow(l, 3, MOD_M) + 295167650*ipow(l, 2, MOD_M) - 310172702*l + 796255993);
					bits_[2].add(r + 1, 199584000*ipow(l, 9, MOD_M) - 694383986*ipow(l, 8, MOD_M) + 567551895*ipow(l, 7, MOD_M) - 295167650*ipow(l, 6, MOD_M) + 752082507*ipow(l, 5, MOD_M) - 737919125*ipow(l, 4, MOD_M) + 989503300*ipow(l, 3, MOD_M) - 295167650*ipow(l, 2, MOD_M) + 310172702*l - 796255993);
					bits_[3].add(l, 598752000*ipow(l, 8, MOD_M) - 185023951*ipow(l, 7, MOD_M) + 324287748*ipow(l, 6, MOD_M) - 590335300*ipow(l, 5, MOD_M) + 253470838*ipow(l, 4, MOD_M) - 650558831*ipow(l, 3, MOD_M) + 989503300*ipow(l, 2, MOD_M) - 530111769*l + 770057572);
					bits_[3].add(r + 1, 401248007*ipow(l, 8, MOD_M) + 185023951*ipow(l, 7, MOD_M) - 324287748*ipow(l, 6, MOD_M) + 590335300*ipow(l, 5, MOD_M) - 253470838*ipow(l, 4, MOD_M) + 650558831*ipow(l, 3, MOD_M) - 989503300*ipow(l, 2, MOD_M) + 530111769*l - 770057572);
					bits_[4].add(l, 802496014*ipow(l, 7, MOD_M) + 573791916*ipow(l, 6, MOD_M) - 486431622*ipow(l, 5, MOD_M) + 737919125*ipow(l, 4, MOD_M) - 253470838*ipow(l, 3, MOD_M) + 737919125*ipow(l, 2, MOD_M) - 494751650*l + 382527944);
					bits_[4].add(r + 1, 197503993*ipow(l, 7, MOD_M) - 573791916*ipow(l, 6, MOD_M) + 486431622*ipow(l, 5, MOD_M) - 737919125*ipow(l, 4, MOD_M) + 253470838*ipow(l, 3, MOD_M) - 737919125*ipow(l, 2, MOD_M) + 494751650*l - 382527944);
					bits_[5].add(l, 676505593*ipow(l, 6, MOD_M) - 88550295*ipow(l, 5, MOD_M) + 486431622*ipow(l, 4, MOD_M) - 590335300*ipow(l, 3, MOD_M) + 752082507*ipow(l, 2, MOD_M) - 295167650*l + 98950330);
					bits_[5].add(r + 1, 323494414*ipow(l, 6, MOD_M) + 88550295*ipow(l, 5, MOD_M) - 486431622*ipow(l, 4, MOD_M) + 590335300*ipow(l, 3, MOD_M) - 752082507*ipow(l, 2, MOD_M) + 295167650*l - 98950330);
					bits_[6].add(l, 323494414*ipow(l, 5, MOD_M) + 573791916*ipow(l, 4, MOD_M) - 324287748*ipow(l, 3, MOD_M) + 295167650*ipow(l, 2, MOD_M) - 250694169*l + 382527944);
					bits_[6].add(r + 1, 676505593*ipow(l, 5, MOD_M) - 573791916*ipow(l, 4, MOD_M) + 324287748*ipow(l, 3, MOD_M) - 295167650*ipow(l, 2, MOD_M) + 250694169*l - 382527944);
					bits_[7].add(l, 197503993*ipow(l, 4, MOD_M) - 185023951*ipow(l, 3, MOD_M) + 567551895*ipow(l, 2, MOD_M) - 370047902*l + 750099172);
					bits_[7].add(r + 1, 802496014*ipow(l, 4, MOD_M) + 185023951*ipow(l, 3, MOD_M) - 567551895*ipow(l, 2, MOD_M) + 370047902*l - 750099172);
					bits_[8].add(l, 401248007*ipow(l, 3, MOD_M) + 694383986*ipow(l, 2, MOD_M) - 891887979*l + 796255993);
					bits_[8].add(r + 1, 598752000*ipow(l, 3, MOD_M) - 694383986*ipow(l, 2, MOD_M) + 891887979*l - 796255993);
					bits_[9].add(l, 199584000*ipow(l, 2, MOD_M) - 598752000*l + 432432000);
					bits_[9].add(r + 1, 800416007*ipow(l, 2, MOD_M) + 598752000*l - 432432000);
					bits_[10].add(l, 59875200 - 39916800*l);
					bits_[10].add(r + 1, 39916800*l - 59875200);
					bits_[11].add(l, 3628800);
					bits_[11].add(r + 1, 996371207);
					break;
			}
		}

		void print_it() {
			std::deque<std::pair<ST,ST>> Q;
			Q.push_back({1, n_});

			while (!Q.empty()) {
				auto [l, r] = Q.front();
				Q.pop_front();

				printf("[%ld - %ld]: %ld\n", l, r, query(l, r));
				if (l == r)
					continue;

				const ST tm = (l + r) / 2;
				Q.push_back({l, tm});
				Q.push_back({tm+1, r});
			}
		}

};



int main(void) {
	UT N, Q;
	scanf("%lu %lu", &N, &Q);

	PowerTree tree(N);

	char buf[5];
	for (UT i = 0; i < Q; i++) {
		scanf("%s", buf);
		if (buf[0] == 'U') {
			UT l, r, k;
			scanf("%lu %lu %lu", &l, &r, &k);
			if (k > 10) {
				throw std::runtime_error("wtf k is larger than 10");
			}
			tree.update(static_cast<ST>(l), static_cast<ST>(r), k);
		} else {
			ST l, r;
			scanf("%ld %ld", &l, &r);
			printf("%ld\n", tree.query(l, r));
		}
	}

	return 0;
}
