#pragma once

#include <vector>
#include <type_traits>
#include <cstdint>
#include <stdexcept>


template<
	typename T,
	typename F,
	typename INV_F,
	T InitElement>
class BIT {
	static_assert(std::is_invocable_r_v<T, F, T, T>, "F needs to be a operator on the domain");
	static_assert(std::is_invocable_r_v<T, INV_F, T, T>, "INV_F needs to be an operator on the domain");
	private:
		F f_{};
		INV_F fi_{};

		std::vector<T> bit_;

	public:
		explicit BIT(std::size_t n) : bit_(n, InitElement) {}

		explicit BIT(const std::vector<T>& a) : BIT(a.size()) {
			for (std::size_t i = 0; i < a.size(); i++) {
				bit_[i] = f_(bit_[i], a[i]);
				std::size_t r = i | (i + 1);
				if (r < a.size())
					bit_[r] = f_(bit_[r], bit_[i]);
			}
		}

		void add(const std::size_t idx, const T delta) {
			const auto N = bit_.size();

			// while we are less than N it's ok.
			for (std::size_t cur = idx; cur < N; cur = cur | (cur+1)) {
				bit_[cur] = f_(bit_[cur], delta);
			}
		}

		[[nodiscard]] T query(std::size_t r) const {
			T ret = InitElement;
			while (true) {
				ret = f_(ret, bit_[r]);

				r = r & (r+1);
				if (r == 0)
					break;

				r--;
			}

			return ret;
		}

		[[nodiscard]] T query(const std::size_t l, const std::size_t r) const {
			if (r < l)
				throw std::runtime_error("r < l is not allowed for query");

			if (l == 0)
				return query(r);
			else
				return fi_(query(r), query(l-1));
		}
};
