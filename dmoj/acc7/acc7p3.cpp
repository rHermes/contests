#include <cstdio>
#include <cstdint>
#include <vector>
#include <stdexcept>
#include <algorithm>

using UT = std::uint32_t;
using ST = std::int32_t;

class DSU {
private:
	using TP = std::uint32_t;

	std::vector<TP> parent_;
	std::vector<TP> size_;

public:

	DSU() = default;

	DSU(TP n) {
		size_.resize(n, 1);
		parent_.resize(n);
		for (TP i = 0; i < n; i++)
			parent_[i] = i;
	}

	[[nodiscard]] TP find(const TP q) {
		if (parent_.size() <= q)
			throw std::runtime_error("Asking about an element out of range");

		const TP qp = parent_[q];
		if (q == qp)
			return q;

		parent_[q] = this->find(qp);
		return parent_[q];
	}

	[[nodiscard]] bool connected(const TP a, const TP b) {
		if (parent_.size() <= a || parent_.size() <= b)
			throw std::runtime_error("Asking about an element out of range");

		return find(a) == find(b);
	}

	[[nodiscard]] TP size(const TP q) {
		if (parent_.size() <= q)
			throw std::runtime_error("Asking about an element out of range");

		const TP qp = this->find(q);

		return size_[qp];
	}
	
	// Returns true if we performed a merge, false otherwise
	bool merge(const TP a, const TP b) {
		if (parent_.size() <= a || parent_.size() <= b)
			throw std::runtime_error("Asking about an element out of range");

		TP ap = this->find(a);
		TP bp = this->find(b);

		if (ap == bp)
			return false;

		if (size_[ap] < size_[bp])
			std::swap(ap, bp);

		parent_[bp] = ap;
		size_[ap] += size_[bp];

		return true;
	}
};

int main() {
	UT N = 0;
	UT M = 0;
	scanf("%u %u", &N, &M);

	std::vector<ST> fs(N);
	for (UT i = 0; i < N; i++) {
		scanf("%d", &fs[i]);
	}

	// It is very interesting, that we have fs[i] < fs[j] <=> i < j
	// We can use this to avoid abs and we can use it here maybe,
	// to avoid actually building an index of all graphs?
	
	DSU tree(N);

	// The total graph will have N-1 edges. We will keep of how many we have
	// created, as we progress through the problem, so we know when to stop.
	UT remaining_edges = N-1;
	// We will union the already known friends.
	for (UT i = 0; i < M; i++) {
		UT x = 0;
		UT y = 0;
		scanf("%u %u", &x, &y);
		
		// this is the same as combining these.
		auto didMerge = tree.merge(x-1, y-1);
		if (!didMerge)
			continue;

		remaining_edges--;
		if (remaining_edges == 0) {
			break;
		}
	}

	// as the weights are always increasing, it means that i < j < k implies
	// that f(k) - f(i) is always going to be bigger than f(k) - f(j)
	//
	// 1 2 100 3000
	//
	// That means that the minimum weights possible in a pass, can be computed by
	// a certain gap, and then we can increase that gap once we have done all of them.
	
	std::uint64_t ans = 0;
	UT gap = 1;
	while (0 < remaining_edges) {
		// We build an array of the minimum weights in this pass.
		// cost, i, j
		std::vector<std::tuple<UT,UT,UT>> passValues;
		for (UT i = 0; i < (N-gap); i++) {
			const UT j = i+gap;

			// we always check if they are in the same, as we can then
			// skip the checks.
			if (tree.connected(i, j))
				continue;

			passValues.emplace_back(fs[j] - fs[i], i, j);
		}
		std::sort(passValues.begin(), passValues.end());


		for (const auto& [f, i, j] : passValues) {
			auto didMerge = tree.merge(i, j);
			if (!didMerge)
				continue;
			
			ans += f;
			remaining_edges--;
			if (remaining_edges == 0)
				break;
		}

		gap += 1;
	}


	printf("%lu\n", ans);

	return 0;
}
