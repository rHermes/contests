#include <cstdint>
#include <vector>
#include <stdexcept>

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
